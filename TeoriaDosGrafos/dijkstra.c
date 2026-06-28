#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5 // Você pode alterar este valor conforme o número de vértices

//Função para encontrar o vértice de menor distância
int minDistancia(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

//Implementação do Algoritmo
void dijkstra(int grafo[V][V], int src) {
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistancia(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && grafo[u][v] && dist[u] != INT_MAX 
                && dist[u] + grafo[u][v] < dist[v])
                dist[v] = dist[u] + grafo[u][v];
    }

    printf("\nVertice \t Distancia da Origem\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

//Função principal do código
int main() {
    int grafo[V][V];
    int origem;

    printf("Digite os valores da matriz de adjacencia (%dx%d):\n", V, V);
    printf("(Use 0 se nao houver conexao direta entre os vertices)\n");

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("Grafo[%d][%d]: ", i, j);
            scanf("%d", &grafo[i][j]);
        }
    }

    printf("\nDigite o vertice de origem (0 a %d): ", V - 1);
    scanf("%d", &origem);

    dijkstra(grafo, origem);

    return 0;
}
