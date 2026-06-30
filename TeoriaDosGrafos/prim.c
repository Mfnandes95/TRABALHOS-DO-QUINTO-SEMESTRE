#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_V 100 
#define INT_MAX 2147483647 

//Procura a chave de valor minímo 
int minKey(int key[], bool visitado[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (visitado[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}
//Função para gerar o algoritmo 
void primMST(int V, int grafo[V][V]) {
    int pai[V], key[V];
    bool visitado[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        visitado[i] = false;
    }

    key[0] = 0;
    pai[0] = -1;

    int pesoTotal = 0; // Variável para o custo total

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, visitado, V);
        if (u == -1) break;

        visitado[u] = true;

        for (int v = 0; v < V; v++) {
            if (grafo[u][v] && visitado[v] == false && grafo[u][v] < key[v]) {
                pai[v] = u;
                key[v] = grafo[u][v];
            }
        }
    }
    
//Função para imprimir o algoritmo
    printf("\nArestas da MST:\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d (Peso: %d)\n", pai[i], i, grafo[i][pai[i]]);
        pesoTotal += grafo[i][pai[i]];
    }
    printf("\nCusto Total da MST: %d\n", pesoTotal); // Requisito atendido
}

//Main 
int main() {
    int V;
    printf("Informe o número de vértices: ");
    if (scanf("%d", &V) != 1 || V <= 0 || V > MAX_V) return 1;

    int grafo[V][V];
    printf("Digite a matriz de adjacência (%dx%d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &grafo[i][j]);
        }
    }

    primMST(V, grafo);
    return 0;
}
