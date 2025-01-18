#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}Node;


Node* createNode(int data) {
    Node* node = (Node*)malloc((sizeof(Node)));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Insert'de baştaki ve sondaki hariç return yok.
Node* insert(Node* root, int data) {

    if(root == NULL) {
        return createNode(data);
    }

    if(data < root->data) {
        root->left = insert(root->left, data);
    } else if(data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

void insertVoid(Node** root, int value) {
    if(*root==NULL) {
        (*root) = createNode(value);
        return;
    }

    if((*root)->data > value) {
        insertVoid(&(*root)->left, value);
    } else if((*root)->data < value) {
        insertVoid(&(*root)->right, value);
    }

}

void inorderTraversal(Node* root) {
    if(root == NULL) return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void preorderTraversal(Node* root) {
    if(root == NULL) return;

    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postOrderTraversal(Node* root) {
    if(root == NULL) return;
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
}

// Her yerde return var.
Node* search(Node* root, int key) {
    if(root == NULL || root->data == key) {
        return root;
    }

    if(key < root->data) {
       return search(root->left, key);
    } else {
       return search(root->right, key);
    }
}

Node* findMin(Node* root) {
    while(root->left != NULL) {
        root = root->left;
    }

    return root;
}

// Başta, sol veya sağı silerken ve de en sonda return var.
Node* deleteNode(Node* root, int value) {
    if(root == NULL) return root;

    if(value < root->data) {
         root->left = deleteNode(root->left, value);
    } else if(value > root->data) {
         root->right = deleteNode(root->right, value);
    } else {
        // We found.
        if(root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if(root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

       Node* temp = findMin(root->right);
        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }

    return root;

}

int main(void) {
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    printf("Before Deletion: ");
    inorderTraversal(root);

    root = deleteNode(root, 50);

    printf("\nAfter Deletion: ");
    inorderTraversal(root);
    return 0;
}
