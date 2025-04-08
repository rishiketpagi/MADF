#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_EDGES 100
#define MAX_VERTICES 100

typedef struct {
    int u, v, cost;
} Edge;

typedef struct {
    Edge edges[MAX_EDGES];
    int size;
} MinHeap;

int parent[MAX_VERTICES];

// Union-Find Initialization
void initializeUnionFind(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}

// Find with path compression
int find(int i) {
    if (parent[i] < 0) return i;
    return parent[i] = find(parent[i]);
}

// Union by rank
void unionSets(int i, int j) {
    int root1 = find(i);
    int root2 = find(j);
    if (root1 != root2) {
        if (parent[root1] < parent[root2]) {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        } else {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
    }
}

// Heapify function to maintain min-heap
void heapify(MinHeap* heap) {
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        int index = i;
        Edge item = heap->edges[i];
        int j = 2 * index + 1;
        while (j < heap->size) {
            if (j + 1 < heap->size && heap->edges[j].cost > heap->edges[j + 1].cost)
                j++;
            if (item.cost <= heap->edges[j].cost)
                break;
            heap->edges[index] = heap->edges[j];
            index = j;
            j = 2 * index + 1;
        }
        heap->edges[index] = item;
    }
}

// Delete min (extract min edge from heap)
Edge delMin(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Heap Empty\n");
        exit(1);
    }
    Edge minEdge = heap->edges[0];
    heap->edges[0] = heap->edges[--heap->size];
    heapify(heap);
    return minEdge;
}

// Kruskal's algorithm with step-by-step output
float kruskal(Edge edges[], int edgeCount, int n) {
    MinHeap heap;
    heap.size = edgeCount;
    for (int i = 0; i < edgeCount; i++) {
        heap.edges[i] = edges[i];
    }

    heapify(&heap);
    initializeUnionFind(n);

    float minCost = 0.0;
    Edge mst[MAX_EDGES];
    int i = 0;

    printf("\n---------------- Kruskal's Stepwise Output ----------------\n");
    printf("|  Edge  |");
    for (int i = 0; i < n; i++) printf(" %2d |", i);
    printf(" j | k | Mincost |\n");

    while (i < n - 1 && heap.size > 0) {
        Edge minEdge = delMin(&heap);
        int j = find(minEdge.u);
        int k = find(minEdge.v);
        if (j != k) {
            mst[i++] = minEdge;
            minCost += minEdge.cost;
            unionSets(j, k);
        }

        printf("| (%d,%d) |", minEdge.u, minEdge.v);
        for (int p = 0; p < n; p++) {
            printf(" %2d |", parent[p] < -1 ? -1 : parent[p]);
        }
        printf(" %d | %d |   %.2f |\n", j, k, minCost);
    }

    if (i != n - 1) {
        printf("No Spanning Tree Found.\n");
        return -1;
    }

    printf("\nMinimum Spanning Tree Edges:\n");
    printf("------------------------------\n");
    printf("| Edge | Vertex 1 | Vertex 2 |\n");
    printf("------------------------------\n");
    for (int j = 0; j < i; j++) {
        printf("| %4d | %8d | %8d |\n", j + 1, mst[j].u, mst[j].v);
    }
    printf("------------------------------\n");

    return minCost;
}

int main() {
    int n, edgeCount;
    Edge edges[MAX_EDGES];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &edgeCount);

    printf("Enter the edges (u, v, cost):\n");
    for (int i = 0; i < edgeCount; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost);
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    float minCost = kruskal(edges, edgeCount, n);

    gettimeofday(&end, NULL);
    long long duration = (end.tv_sec - start.tv_sec) * 1000000000LL +
                         (end.tv_usec - start.tv_usec) * 1000LL;

    if (minCost != -1) {
        printf("\nMinimum Cost of Spanning Tree: %.2f\n", minCost);
        printf("Kruskal execution time: %lld nanoseconds\n", duration);
    }

    return 0;
}
