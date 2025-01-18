#include <stdio.h>
#include <stdlib.h>
#include <arm/limits.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right= NULL;

    return newNode;
}

Node* insert(Node* root, int data) {
    if(root == NULL) {
        return createNode(data);
    }

    if(data > root->data) {
      root->right = insert(root->right, data);
    } else if(data < root->data) {
      root->left = insert(root->left, data);
    }

    return root;
}

void inorderTraversal(Node* root) {
    if(root == NULL) return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);

}

void insertQuestion(Node* root) {
    insert(root, 5);
    insert(root, 4);
    insert(root, 6);


    insert(root, 1);
    insert(root, -7);
    insert(root, -3);

    insert(root, 0);
    insert(root, -5);


    inorderTraversal(root);

    printf("\n");
}

int search(Node* root, int key) {
    if(root == NULL) return 0;
    if(root->data == key) return 1;

    if(key>root->data) return search(root->right, key);

    return search(root->left, key);

}

void searchQuestion(Node* root) {
    int fiveExists = search(root, -10);
    printf("Does five exist: %d", fiveExists);
}

Node *findMin(Node* root) {
    while(root->left !=NULL) {
        root = root->left;
    }

    return root;

}

Node *deleteNode(Node* root, int key) {
    if(root == NULL) return root;

    if(key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if(root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = findMin(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);

    }

    return root;

}

void deleteQuestion(Node* root) {
    deleteNode(root,0);
    inorderTraversal(root);
    printf("\n");
}

int height(Node*root) {
    if(root == NULL) return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

void heightQuestion(Node* root) {
    int h = height(root);
    printf("Height of this tree is: %d\n", h);
    printf("\n");
}

int isBSTUtil(Node* root, int min, int max) {
    if(root == NULL) return 1;

    if(root->data <= min || root->data >= max) return 0;

    return isBSTUtil(root->left, min, root->data) && isBSTUtil(root->right, root->data, max);

}

int isBST(Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

int main(void)
{

    Node* root = createNode(2);

    root->left = createNode(5);
    root->right = createNode(7);

    int isGood = isBST(root);

    printf("%d\n", isGood);


    free(root);

    return 0;
}
