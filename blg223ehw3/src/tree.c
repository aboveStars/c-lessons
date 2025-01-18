#include "../include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

TreeNode *init_node(GameState *gs) {
    if (!gs) return NULL;

    TreeNode *newNode = malloc(sizeof(TreeNode));
    if (!newNode) return NULL;

    newNode->num_children = -1;
    newNode->game_state = gs;
    newNode->children = NULL;

    return newNode;
}

TreeNode *init_tree(GameState *gs, int depth) {
    if (!gs) return NULL;

    TreeNode *root = init_node(gs);
    if (!root) return NULL;

    if (get_game_status(gs) != IN_PROGRESS) {
        root->num_children = -1;
        root->children = NULL;
        return root;
    }

    // Base case: depth = 1 or game is finished
    if (depth <= 1) {
        root->num_children = -1;
        root->children = NULL;
        return root;
    }

    bool moves[7] = {false};
    int num_moves = available_moves(gs, moves);

    if (num_moves == 0) {
        root->num_children = -1;
        root->children = NULL;
        return root;
    }

    // Initialize children array
    root->num_children = num_moves;
    root->children = malloc(sizeof(TreeNode *) * num_moves);
    if (!root->children) {
        free(root);
        return NULL;
    }

    // Create children recursively
    int child_idx = 0;
    for (int i = 0; i < gs->width; i++) {
        if (moves[i]) {
            GameState *new_state = make_move(gs, i);
            if (!new_state) {
                for (int j = 0; j < child_idx; j++) {
                    free_tree(root->children[j]);
                }
                free(root->children);
                free(root);
                return NULL;
            }

            if (depth == 2) {
                // For depth 2, children are leaf nodes
                root->children[child_idx] = init_node(new_state);
                if (!root->children[child_idx]) {
                    free_game_state(new_state);
                    for (int j = 0; j < child_idx; j++) {
                        free_tree(root->children[j]);
                    }
                    free(root->children);
                    free(root);
                    return NULL;
                }
                root->children[child_idx]->num_children = -1;
            } else {
                // For depth > 2, recursively build subtrees
                root->children[child_idx] = init_tree(new_state, depth - 1);
                if (!root->children[child_idx]) {
                    free_game_state(new_state);
                    for (int j = 0; j < child_idx; j++) {
                        free_tree(root->children[j]);
                    }
                    free(root->children);
                    free(root);
                    return NULL;
                }
            }
            child_idx++;
        }
    }

    return root;
}

void free_tree(TreeNode *root) {
    if (!root) return;

    if (root->children) {
        for (int i = 0; i < root->num_children; i++) {
            free_tree(root->children[i]);
        }
        free(root->children);
    }

    if (root->game_state) {
        free_game_state(root->game_state);
    }

    free(root);
}

void expand_node(TreeNode *node) {
    if (!node || node->num_children != -1) return;

    if (get_game_status(node->game_state) != IN_PROGRESS) {
        node->num_children = -1;
        return;
    }

    bool moves[7] = {false};
    int num_moves = available_moves(node->game_state, moves);

    if (num_moves == 0) {
        node->num_children = -1;
        return;
    }

    node->num_children = num_moves;
    node->children = malloc(sizeof(TreeNode *) * num_moves);
    if (!node->children) {
        node->num_children = -1;
        return;
    }

    int child_idx = 0;
    for (int i = 0; i < node->game_state->width; i++) {
        if (moves[i]) {
            GameState *new_state = make_move(node->game_state, i);
            if (!new_state) continue;

            node->children[child_idx] = init_node(new_state);
            if (!node->children[child_idx]) {
                free_game_state(new_state);
                for (int j = 0; j < child_idx; j++) {
                    free_tree(node->children[j]);
                }
                free(node->children);
                node->children = NULL;
                node->num_children = -1;
                return;
            }
            node->children[child_idx]->num_children = -1;
            child_idx++;
        }
    }
}

void expand_tree(TreeNode *root) {
    if (!root) return;

    // Find all leaf nodes (nodes with num_children == -1)
    if (root->num_children == -1) {
        expand_node(root);
    } else if (root->num_children > 0) {
        bool all_leaves_expanded = true;
        // First try to expand any unexpanded leaf nodes
        for (int i = 0; i < root->num_children; i++) {
            if (root->children[i]->num_children == -1) {
                expand_node(root->children[i]);
                all_leaves_expanded = false;
            }
        }

        // If all immediate children are expanded, go deeper
        if (all_leaves_expanded) {
            for (int i = 0; i < root->num_children; i++) {
                expand_tree(root->children[i]);
            }
        }
    }
}

int node_count(TreeNode *root) {
    if (!root) return 0;

    int count = 1;
    if (root->children) {
        for (int i = 0; i < root->num_children; i++) {
            count += node_count(root->children[i]);
        }
    }

    return count;
}
