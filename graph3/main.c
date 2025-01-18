#include <stdio.h>
#include <limits.h>

#define V 5 // Number of vertices in the graph

// Function to find the vertex with the minimum distance value
int findMinimum(const int dist[], const int checked[]) {
    int min = INT_MAX;
    int minIndex = -1;

    for(int i = 0; i< V; i++) {
        if(!checked[i] && dist[i] < min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int graph[V][V], const int src) {
    int dist[V];
    int checked[V];

    for(int i=0; i<V; i++) {
        dist[i] = INT_MAX;
        checked[i] = 0;
    }

    dist[src] = 0;

    for(int i = 0; i<V; i++) {
        int u = findMinimum(dist, checked);
        checked[u] = 1;

        for(int v=0; v<V; v++) {
            if(!checked[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v] ) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Vertex\tDistance from Source (%d)\n", src);
    for(int i=0; i<V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }

}

int main() {
    // Example graph as an adjacency matrix
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}
    };

    int source = 3; // Starting vertex
    dijkstra(graph, source);

    return 0;
}
