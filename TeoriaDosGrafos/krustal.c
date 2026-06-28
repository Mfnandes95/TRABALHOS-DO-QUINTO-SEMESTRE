#include <stdio.h>
#include <stdlib.h>

// Arestas 
struct Aresta {
    int origem, destino, peso;
};

// Grafo
struct Grafo {
    int V, A;
    struct Aresta* aresta; // Corrigido para ponteiro
};

// Conjuntos disjuntos
struct Conjunto {
    int pai;
    int rank;
};

// Cria o Grafo com V vertices e A arestas
struct Grafo* criarGrafo(int V, int A){
    struct Grafo* grafo = (struct Grafo*) malloc(sizeof(struct Grafo));
    grafo->V = V;
    grafo->A = A;
    grafo->aresta = (struct Aresta*)malloc(A * sizeof(struct Aresta));
    return grafo;
};

// Encontra o conjunto de um elemento i (usando path compression)
// Corrigido para struct Conjunto (C é case-sensitive)
int busca(struct Conjunto conjunto[], int i){
    if (conjunto[i].pai != i)
        conjunto[i].pai = busca(conjunto, conjunto[i].pai);
    return conjunto[i].pai;
}

// União de dois conjuntos
// Corrigido para struct Conjunto
void uniao(struct Conjunto conjunto[], int x, int y){
    int xroot = busca(conjunto, x);
    int yroot = busca(conjunto, y);

    if (conjunto[xroot].rank < conjunto[yroot].rank)
        conjunto[xroot].pai = yroot;
    else if (conjunto[xroot].rank > conjunto[yroot].rank)
        conjunto[yroot].pai = xroot;
    else {
        conjunto[yroot].pai = xroot;
        conjunto[xroot].rank++;
    }
}

// Compara duas arestas pelo peso
int comparaArestas(const void* a, const void* b){
    struct Aresta* arestaA = (struct Aresta*)a;
    struct Aresta* arestaB = (struct Aresta*)b;
    return arestaA->peso - arestaB->peso;
}

// Função principal do Algoritmo de Kruskal
void krustal(struct Grafo* grafo){
    int V = grafo->V;
    struct Aresta resultado[V]; 
    int e = 0; 
    int i = 0; 

    qsort(grafo->aresta, grafo->A, sizeof(struct Aresta), comparaArestas);

    struct Conjunto* conjunto = (struct Conjunto*) malloc(V * sizeof(struct Conjunto));
    for (int v = 0; v < V; ++v) {
        conjunto[v].pai = v;
        conjunto[v].rank = 0;
    }

    while (e < V - 1 && i < grafo->A) {
        struct Aresta proximaAresta = grafo->aresta[i++];

        int x = busca(conjunto, proximaAresta.origem);
        int y = busca(conjunto, proximaAresta.destino);

        if (x != y) {
            resultado[e++] = proximaAresta;
            uniao(conjunto, x, y);
        }
    }

    printf("Arestas na Árvore Geradora Mínima:\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", resultado[i].origem, resultado[i].destino, resultado[i].peso);
        
    free(conjunto); // Boa prática: liberar a memória alocada dentro da função
}

int main() {
    int V, A;
    printf("Digite o número de vértices e arestas: ");
    if(scanf("%d %d", &V, &A) != 2) return 1;

    struct Grafo* grafo = criarGrafo(V, A);

    printf("Digite as arestas (origem destino peso):\n");
    for (int i = 0; i < A; i++) {
        scanf("%d %d %d", &grafo->aresta[i].origem, &grafo->aresta[i].destino, &grafo->aresta[i].peso);
    }

    krustal(grafo);

    free(grafo->aresta);
    free(grafo);
    return 0;
}
