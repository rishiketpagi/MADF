#include <stdio.h>
#include <limits.h>
#include <sys/time.h>
#define MAX 30
struct Edges {
    int ori, dest;  };
int max_edges, n, count = 0;
int t[MAX][2], near[MAX], cost[MAX][MAX];
struct Edges E[MAX];
int prims(struct Edges E[MAX], int cost[MAX][MAX], int n, int t[MAX][2]) {
    int i, j, k, l, m, index, o, d;
    int mincost = INT_MAX;
    if (count == 0) {
printf("No valid edges entered.\n");
        return -1;   }
 for (i = 1; i <= count; i++) {
        o = E[i].ori;
        d = E[i].dest;
        if (cost[o][d] < mincost) {
            mincost = cost[o][d];
            k = o;
            l = d;  }
    }
    t[1][0] = k;
    t[1][1] = l;
    for (i = 1; i <= n; i++)
near[i] = (cost[i][l] < cost[i][k]) ? l : k;
    near[k] = near[l] = 0;
printf("\n-------------------------------------------\n");
printf("|  Vertex  |  Near[j]  | Cost[j, Near[j]] |\n");
printf("-------------------------------------------\n");
    for (i = 1; i <= n; i++) {
        if (near[i] == 0)
printf("| near[%d]  |  %-7d  |        -         |\n", i, near[i]);
else if (cost[i][near[i]] == INT_MAX)
printf("| near[%d]  |  %-7d  |        INF       |\n", i, near[i]);
else
printf("| near[%d]  |  %-7d  |        %-4d      |\n", i, near[i], cost[i][near[i]]);
    }
printf("-------------------------------------------\n");
printf("Minimum Cost = %d\n", mincost);
for (i = 2; i <= n - 1; i++) {
        m = INT_MAX;
        for (j = 1; j <= n; j++) {
if (near[j] != 0 && cost[j][near[j]] < m) {
                index = j;
           m = cost[j][near[j]];   }
        }
        t[i][0] = index;
        t[i][1] = near[index];
        mincost += m;
        near[index] = 0;
        for (k = 1; k <= n; k++) {
if (near[k] != 0 && cost[k][near[k]] > cost[k][index])
           near[k] = index;   }
printf("\n-------------------------------------------\n");
printf("|  Vertex  |  Near[j]  | Cost[j, Near[j]] |\n");
printf("-------------------------------------------\n");
for (j = 1; j <= n; j++) {
            if (near[j] == 0)
printf("| near[%d]  |  %-7d  |        -         |\n", j, near[j]);
else if (cost[j][near[j]] == INT_MAX)
printf("| near[%d]  |  %-7d  |        INF       |\n", j, near[j]);
else
printf("| near[%d]  |  %-7d  |        %-4d      |\n", j, near[j], cost[j][near[j]]);     }
printf("-------------------------------------------\n");
printf("Minimum Cost = %d\n", mincost);    }
    return mincost;
}
void create_graph() {
    int origin, destin, weight;
printf("Enter the number of vertices: ");
scanf("%d", &n);
max_edges = (n * (n - 1)) / 2;
for (int i = 0; i <= n; i++)
for (int j = 0; j <= n; j++)
cost[i][j] = INT_MAX;
printf("Enter the edges and their cost (source, destination, cost) (-1 -1 -1 to quit):\n");
for (int i = 1; i <= max_edges; i++) {
printf("Edge %d : ", i);
scanf("%d%d%d", &origin, &destin, &weight);
if (origin == -1 && destin == -1 && weight == -1)
 break;
if (origin < 1 || destin < 1 || origin > n || destin > n) {
printf("Invalid vertex! Try again.\n");
        i--;
        continue;
        }
cost[origin][destin] = weight;
cost[destin][origin] = weight;
        count++;
        E[count].ori = origin;
        E[count].dest = destin; }
}

int main() {
    int m;
    struct timeval start, end;
    long s, us;
    double t_ms;
    create_graph();
gettimeofday(&start, NULL);
    m = prims(E, cost, n, t);
gettimeofday(&end, NULL);
    s = end.tv_sec - start.tv_sec;
us = end.tv_usec - start.tv_usec;
t_ms = (s * 1000000 + us) / 1000.0;
if (m != -1) {
printf("\nFinal Minimum Spanning Tree Edges:\n");
printf("-----------------------------\n");
printf("|  T  | Vertex 1 | Vertex 2 |\n");
printf("-----------------------------\n");
for (int i = 1; i < n; i++)
printf("| %2d  |    %-4d  |    %-4d  |\n",i, t[i][0], t[i][1]);
printf("-----------------------------\n");
printf("\nExecution time of Prim's function: %f ms\n", t_ms);
    }
    return 0;
} 
