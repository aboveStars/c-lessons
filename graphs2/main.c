#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node;

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = data;
    node->next = NULL;

    return node;
}

void addEdge(Node* adj[4], int i, int j) {
   Node* newNode = createNode(j);
    newNode->next = adj[i];
    adj[i] = newNode;

    Node* otherNewNode = createNode(i);
    otherNewNode->next = adj[j];
    adj[j] = otherNewNode;
}

void displayAdjList(Node* adj[4]) {
    for (int i=0; i<4; i++) {
       printf("%d: ", i);

        Node* crr = adj[i];
        while(crr != NULL) {
            printf("%d -> ", crr->data);
            crr = crr->next;
        }

        printf("\n");
    }
}

int main(void) {
    int V = 4;

    Node* adj[V];

    for(int i=0 ; i<V; i++) {
        adj[i] = NULL;
    }

    addEdge(adj, 0,1);
    addEdge(adj, 0,2);
    addEdge(adj, 1,2);
    addEdge(adj, 2,3);

    displayAdjList(adj);

    return 0;
}
