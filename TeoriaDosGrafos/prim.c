#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_V 100 // Tamanho máximo suportado para o grafo
#define INT_MAX 2147483647 // Valor máximo para inicializar as chaves

// Função para achar o vértice de menor chave
int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Implementação do algoritmo de Prim
void primMST(int V, int grafo[V][V]) {
    int pai[V]; // Array de armazenamento do MST
    int key[V]; // Chaves para verificação de peso
    bool visitado[V]; // Array para verificar se o vértice foi incluído no MST

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        visitado[i] = false;
    }

    // Primeiro vértice participante da MST
    key[0] = 0; // Chave do primeiro vértice
    pai[0] = -1; // Primeiro vértice não tem pai

    // A MST tem V vértices
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, visitado, V); // Escolhe o vértice de menor chave
        if (u == -1) {
            break;
        }

        visitado[u] = true; // Marcação do vértice visitado

        // Atualização das chaves dos vértices
        for (int v = 0; v < V; v++) {
            if (grafo[u][v] && visitado[v] == false && grafo[u][v] < key[v]) {
                pai[v] = u;
                key[v] = grafo[u][v];
            }
        }
    }

    // Imprime a MST
    printf("Aresta Peso\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d %d\n", pai[i], i, grafo[i][pai[i]]);
    }
}

int main() {
    int V;
    printf("Informe o número de vértices: ");
    if (scanf("%d", &V) != 1 || V <= 0 || V > MAX_V) {
        fprintf(stderr, "Número de vértices inválido.\n");
        return 1;
    }

    int grafo[V][V];
    printf("Digite a matriz de adjacência (%d x %d), usando 0 para nenhuma aresta:\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (scanf("%d", &grafo[i][j]) != 1) {
                fprintf(stderr, "Entrada inválida de peso.\n");
                return 1;
            }
        }
    }

    primMST(V, grafo);
    return 0;
}

