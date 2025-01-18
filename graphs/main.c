#include <stdio.h>

void addEdge(int mat[4][4], int i, int j) {
    mat[i][j] = 1;
    mat[j][i] = 1;
}

void displayMatrix(int mat[4][4]) {
    for (int i=0; i<4; i++) {
        for(int j=0; j< 4; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {

    int mat[4][4] = {0};

    addEdge(mat, 0, 1);
    addEdge(mat, 0, 2);
    addEdge(mat, 1, 2);
    addEdge(mat, 2, 3);

    displayMatrix(mat);

    return 0;
}
