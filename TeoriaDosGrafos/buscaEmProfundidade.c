#include <stdio.h>
#include <stdlib.h>

#define MAXV 100

int adj[MAXV][MAXV];
int visited[MAXV];
int n;

void dfs(int u) {
    visited[u] = 1;
    printf("%d ", u);

    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v);
        }
    }
}

int main(void) {
    int m;
    int start;

    printf("Numero de vertices e arestas: ");
    if (scanf("%d %d", &n, &m) != 2) return 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
        visited[i] = 0;
    }

    printf("Arestas (u v):\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < n && v >= 0 && v < n) {
            adj[u][v] = 1;
            adj[v][u] = 1;
        }
    }

    printf("Vertice inicial: ");
    scanf("%d", &start);
    printf("DFS: ");
    dfs(start);
    printf("\n");

    return 0;
}
