#include <stdio.h>

#define V 5  
#define E 7 


typedef struct {
    int u, v, weight;
} Edge;


int parent[V];

int find(int i) {
    if (parent[i] == i)
        return i;
    else
        return find(parent[i]);
}

void unionSets(int rootX, int rootY) {
        parent[rootY] = rootX;  // Merge the sets
}

void sortEdges(Edge edges[]) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = i + 1; j < E; j++) {
            if (edges[i].weight > edges[j].weight) {
                
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

void kruskalMST(Edge edges[]) {
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    sortEdges(edges);  

    printf("Edges in the Minimum Spanning Tree:\n");
    int mstWeight = 0;
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(u) != find(v)) {  // If they are not in the same set
            unionSets(find(u), find(v));
            printf("%d - %d : %d\n", u, v, edges[i].weight);
            mstWeight += edges[i].weight;
        }
    }

    printf("\nTotal weight of MST: %d\n", mstWeight);
}


int main() {
    Edge edges[E] = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3},
        {1, 3, 8}, {1, 4, 5}, {2, 4, 7}, {3, 4, 9}
    };

    kruskalMST(edges);

    return 0;
}
