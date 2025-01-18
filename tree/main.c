#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void inorderTraversal(const Node* node) {
    if(node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        inorderTraversal(node->right);
    }
}


void preorderTraversal(const Node* node) {
    if(node != NULL) {
        printf("%d ", node->data);
        inorderTraversal(node->left);
        inorderTraversal(node->right);
    }
}

void postorderTraversal(const Node* node) {
    if(node != NULL) {
        inorderTraversal(node->left);
        inorderTraversal(node->right);
        printf("%d ", node->data);
    }
}


Node* insert(Node* root, int data) {
    if(root == NULL) {
        return createNode(data);
    }

    if(data > root->data) {
        root->right = insert(root->right, data);
    } else if(data < root->data){
        root->left = insert(root->left, data);
    } else {
        return root;
    }

    return root;
}


int search(Node* root, int key) {
    if(root == NULL) return 0;
    if(root->data == key) return 1;

    if(root->data > key) return search(root->left, key);
    return search(root->right, key);

}

int main(void) {

    Node* root = createNode(1);

    root->left = createNode(2);
    root->right = createNode(3);

    root->left->left= createNode(4);
    root->left->right = createNode(5);

    inorderTraversal(root);

    printf("\n");

    preorderTraversal(root);

    printf("\n");

    postorderTraversal(root);

    insert(root, 6);

    printf("\n");

    inorderTraversal(root);

    printf("\n");

    int index = search(root, 10);

    printf("%d \n", index);

    free(root);

    //printf("Hello, World!\n");
    return 0;
}
