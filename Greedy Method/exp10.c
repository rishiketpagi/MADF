#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>  // For gettimeofday()

#define MAX 100

int minDistance(int dist[], bool s[], int n) {
    int min = INT_MAX, min_index;
    for (int v = 1; v <= n; v++)
        if (!s[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void single_shortest_path(int graph[MAX][MAX], int v, int n) {
    int dist[MAX], parent[MAX];
    bool s[MAX];
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        s[i] = false;
        parent[i] = -1;
    }
    dist[v] = 0;

    printf("\nIterations:\n");
    for (int count = 1; count < n; count++) {
        int u = minDistance(dist, s, n);
        s[u] = true;

        printf("Iteration %d: u = %d\n", count, u);
        printf("S[");
        bool first = true;
        for (int i = 1; i <= n; i++) {
            if (s[i]) {
                if (!first) printf("=S[%d]", i);
                else { printf("%d]", i); first = false; }
            }
        }
        printf(" = true\n");
        printf("S[");
        first = true;
        for (int i = 1; i <= n; i++) {
            if (!s[i]) {
                if (!first) printf("=S[%d]", i);
                else { printf("%d]", i); first = false; }
            }
        }
        printf(" = false\n");

        for (int w = 1; w <= n; w++) {
            if (!s[w] && graph[u][w] && dist[u] != INT_MAX && dist[u] + graph[u][w] < dist[w]) {
                dist[w] = dist[u] + graph[u][w];
                parent[w] = u;
            }
        }

        for (int i = 1; i <= n; i++) {
            printf("dist[%d] = ", i);
            if (dist[i] == INT_MAX)
                printf("INF\n");
            else
                printf("%d\n", dist[i]);
        }
        printf("\n");
    }

    printf("\nFinal Shortest Paths:\n");
    for (int i = 1; i <= n; i++) {
        printf("source:1, destination:%d, ", i);
        if (dist[i] == INT_MAX) {
            printf("No Path\n");
            continue;
        }
        printf("Length = %d, Path = ", dist[i]);
        int path[MAX], index = 0, temp = i;
        while (temp != -1) {
            path[index++] = temp;
            temp = parent[temp];
        }
        for (int j = index - 1; j >= 0; j--)
            printf("%d%s", path[j], (j > 0) ? " -> " : "");
        printf("\n");
    }
}

int main() {
    int n, e, u, v, w, graph[MAX][MAX] = {0};
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);
    printf("Enter edges (from to weight):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
    }
    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);

    // Time measurement
    struct timeval start, end;
    gettimeofday(&start, NULL);

    single_shortest_path(graph, source, n);

    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("\nExecution time: %.6f seconds\n", elapsed);

    return 0;
}
