#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int origem;
    int destino;
    int peso;
} Aresta;

typedef struct {
    int V; 
    int E; 
    Aresta* arestas;
} Grafo;

typedef struct {
    int pai;
    int rank;
} Subset;

Grafo* criarGrafo(int V, int E) {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->V = V;
    grafo->E = E;
    grafo->arestas = (Aresta*) malloc(E * sizeof(Aresta));
    return grafo;
}

int find(Subset subsets[], int i) {
    if (subsets[i].pai != i)
        subsets[i].pai = find(subsets, subsets[i].pai);
    return subsets[i].pai;
}

void unionConjuntos(Subset subsets[], int x, int y) {
    int raizX = find(subsets, x);
    int raizY = find(subsets, y);

    if (subsets[raizX].rank < subsets[raizY].rank)
        subsets[raizX].pai = raizY;
    else if (subsets[raizX].rank > subsets[raizY].rank)
        subsets[raizY].pai = raizX;
    else {
        subsets[raizY].pai = raizX;
        subsets[raizX].rank++;
    }
}

int compararArestas(const void* a, const void* b) {
    Aresta* arestaA = (Aresta*)a;
    Aresta* arestaB = (Aresta*)b;
    return arestaA->peso - arestaB->peso;
}

void KruskalMST(Grafo* grafo) {
    int V = grafo->V;
    Aresta resultado[V]; 
    int e = 0; 
    int i = 0; 

    qsort(grafo->arestas, grafo->E, sizeof(Aresta), compararArestas);

    Subset* subsets = (Subset*) malloc(V * sizeof(Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].pai = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < grafo->E) {
        Aresta proximaAresta = grafo->arestas[i++];
        int x = find(subsets, proximaAresta.origem);
        int y = find(subsets, proximaAresta.destino);

        if (x != y) {
            resultado[e++] = proximaAresta;
            unionConjuntos(subsets, x, y);
        }
    }

    printf("\n--- Resultado: Arvore Geradora Minima ---\n");
    int custoMinimo = 0;
    for (i = 0; i < e; ++i) {
        printf("Aresta %d-%d com peso %d\n", resultado[i].origem, resultado[i].destino, resultado[i].peso);
        custoMinimo += resultado[i].peso;
    }
    printf("Custo Total da MST: %d\n", custoMinimo);

    free(subsets);
}

int main() {
    int V, E;
    printf("Digite o numero de vertices: ");
    scanf("%d", &V);
    printf("Digite o numero de arestas: ");
    scanf("%d", &E);

    Grafo* grafo = criarGrafo(V, E);

    printf("\nDigite as arestas no formato (origem destino peso):\n");
    for (int i = 0; i < E; i++) {
        printf("Aresta %d: ", i + 1);
        scanf("%d %d %d", &grafo->arestas[i].origem, &grafo->arestas[i].destino, &grafo->arestas[i].peso);
    }

    KruskalMST(grafo);

    free(grafo->arestas);
    free(grafo);
    return 0;
}
