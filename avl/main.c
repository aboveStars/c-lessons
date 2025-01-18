#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
}Node;

int getHeight(Node* node) {
    if(node == NULL) return 0;
    return node->height;
}

int getBalanceFactor(Node* node) {
    if(node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);

}

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;

    node->left = NULL;
    node->right = NULL;

    node->height = 1;

    return node;
}

int max(int a, int b) {
    return a > b ? a : b;
}

Node* rightRotate(Node* y) {
    // Defines
    Node* x = y->left;
    Node* t2 = x->right;

    // Rotation
    x->right = y;
    y->left = t2;

    // Update Heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // New Pivot
    return x;
}

Node* leftRotate(Node* x) {
    // Defines
    Node* y = x->right;
    Node* t2 = y->left;

    // Rotation
    y->left= x;
    x->right = t2;

    // Update Heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // New Pivot
    return y;
}

Node* insert(Node* node, int value) {
    if(node == NULL) {
        return createNode(value);
    }

    if(value < node->data) {
        node->left = insert(node->left, value);
    } else if(value > node->data) {
        node->right = insert(node->right, value);
    } else {
        return node;
    }

    // Update Height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Get Balance
    int balance = getBalanceFactor(node);

    // Left - Left
    if(balance > 1 && value < node->left->data) {
        return rightRotate(node);
    }

    // Left - Right
    if(balance > 1 && value > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right - Right
    if(balance < -1 && value > node->right->data) {
        return leftRotate(node);
    }

    // Right - Left
    if(balance < -1 && value < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;

}

void inorderTraversal(Node* node) {
    if(node == NULL) return;

    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

int main(void) {
    Node* root = NULL;

    // Insert values
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Print the tree
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
