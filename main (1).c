#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 20
#define INF 1000000000

// 1. BUSCA EM PROFUNDIDADE (DFS)
// Procura recursivamente um caminho aumentante na rede residual
bool dfs(int redeResidual[MAX_VERTICES][MAX_VERTICES], int V, int u, int destino, bool visitado[], int pai[]) {
    visitado[u] = true;

    if (u == destino) {
        return true;
    }

    for (int v = 0; v < V; v++) {
        // Se o vizinho nao foi visitado e o "cano" ainda tem capacidade livre
        if (!visitado[v] && redeResidual[u][v] > 0) {
            pai[v] = u; // Guarda de onde viemos
            if (dfs(redeResidual, V, v, destino, visitado, pai)) {
                return true;
            }
        }
    }
    return false;
}

// 2. EXIBIÇÃO DO RELATÓRIO DE OCUPAÇÃO (Mapeamento de Uso)
// Mostra a capacidade original, quanto foi usado e se a aresta saturou
void exibirRelatorio(int original[MAX_VERTICES][MAX_VERTICES], int residual[MAX_VERTICES][MAX_VERTICES], int V) {
    printf("\n===================================================\n");
    printf("        RELATORIO FINAL DE OCUPACAO DA REDE        \n");
    printf("===================================================\n");
    printf("ARESTA\t\tCAPACIDADE\tUSO\t\tSTATUS\n");
    printf("---------------------------------------------------\n");
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (original[i][j] > 0) {
                // O fluxo que passou é a diferença entre a capacidade inicial e a residual restante
                int fluxo_passado = original[i][j] - residual[i][j];
                
                printf("%d -> %d\t\t%d\t\t%d\t\t%s\n", 
                        i, j, original[i][j], fluxo_passado, 
                        (fluxo_passado == original[i][j]) ? "[CHEIO]" : "[DISPONIVEL]");
            }
        }
    }
    printf("===================================================\n");
}

// 3. MOTOR DO ALGORITMO (Ford-Fulkerson)
int fordFulkerson(int grafo[MAX_VERTICES][MAX_VERTICES], int V, int origem, int destino) {
    int u, v;
    int redeResidual[MAX_VERTICES][MAX_VERTICES];

    // Inicializa a rede residual clonando o grafo original
    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++) {
            redeResidual[u][v] = grafo[u][v];
        }
    }

    int pai[MAX_VERTICES];
    bool visitado[MAX_VERTICES];
    int fluxo_maximo = 0;

    printf("\n--- Caminhos Encontrados pela DFS ---\n");

    // Enquanto a DFS conseguir achar uma rota transitavel da origem ao destino
    while (1) {
        memset(visitado, 0, sizeof(visitado));

        if (!dfs(redeResidual, V, origem, destino, visitado, pai)) {
            break; // Rede saturada, fim da linha
        }

        // Encontra o gargalo (menor capacidade residual) do caminho atual
        int fluxo_caminho = INF;
        for (v = destino; v != origem; v = pai[v]) {
            u = pai[v];
            if (redeResidual[u][v] < fluxo_caminho) {
                fluxo_caminho = redeResidual[u][v];
            }
        }

        // Imprime o caminho encontrado de trás para frente
        printf("Caminho: ");
        int atual = destino;
        while (atual != -1) {
            printf("%d", atual);
            atual = (atual == origem) ? -1 : pai[atual];
            if (atual != -1) printf(" <- ");
        }
        printf(" | Gargalo: %d\n", fluxo_caminho);

        // Atualiza a rede residual (arestas diretas e reversas)
        for (v = destino; v != origem; v = pai[v]) {
            u = pai[v];
            redeResidual[u][v] -= fluxo_caminho;
            redeResidual[v][u] += fluxo_caminho;
        }

        fluxo_maximo += fluxo_caminho;
    }

    // Chama o relatório passando o grafo original, a residual modificada e o número de vértices
    exibirRelatorio(grafo, redeResidual, V);

    return fluxo_maximo;
}

// 4. FUNÇÃO PRINCIPAL E INTERFACE DINÂMICA
int main() {
    int V;
    int grafo[MAX_VERTICES][MAX_VERTICES];

    memset(grafo, 0, sizeof(grafo));

    printf("=== CONFIGURACAO DO GRAFO ===\n");
    printf("Digite o numero total de vertices (max %d): ", MAX_VERTICES);
    if (scanf("%d", &V) != 1 || V <= 0 || V > MAX_VERTICES) {
        printf("Quantidade invalida!\n");
        return 1;
    }

    printf("\n=== INSERCAO DINAMICA DE ARESTAS ===\n");
    printf("Digite as arestas no formato: [origem] [destino] [capacidade]\n");
    printf("Para ENCERRAR a insercao, digite -1 na origem.\n");
    printf("---------------------------------------------------\n");

    while (true) {
        int u, v, cap;
        printf("Adicionar Aresta (ou -1 para sair): ");
        if (scanf("%d", &u) != 1) return 1;
        
        if (u == -1) {
            break; // Sai do loop de inserção de forma segura
        }

        if (scanf("%d %d", &v, &cap) != 2) return 1;

        // Validacoes de segurança antes de alocar na matriz
        if (u >= 0 && u < V && v >= 0 && v < V) {
            if (cap >= 0) {
                grafo[u][v] = cap;
                printf(" -> Sucesso: %d -> %d adicionado com capacidade %d.\n", u, v, cap);
            } else {
                printf(" -> Erro: Capacidade nao pode ser negativa!\n");
            }
        } else {
            printf(" -> Erro: Vertices devem estar entre 0 e %d.\n", V - 1);
        }
    }

    int origem, destino;
    printf("\n=== DEFINICAO DOS PONTOS DE FLUXO ===\n");
    printf("Defina o vertice de Origem (Source): ");
    if (scanf("%d", &origem) != 1) return 1;
    printf("Defina o vertice de Destino (Sink): ");
    if (scanf("%d", &destino) != 1) return 1;

    if (origem < 0 || origem >= V || destino < 0 || destino >= V || origem == destino) {
        printf("Origem ou Destino invalidos!\n");
        return 1;
    }

    // Execução do algoritmo
    int fluxo_total = fordFulkerson(grafo, V, origem, destino);

    printf("\n>>> FLUXO MAXIMO TOTAL ALCANCADO: %d <<<\n\n", fluxo_total);

    return 0;
}