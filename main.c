#include <stdio.h>
#include <stdlib.h>

// Função para verificar se o conjunto E está vazio
int isEmpty(int* E, int n) {
    for (int i = 1; i <= n; i++) {
        if (E[i] != 0) {
            return 0;
        }
    }
    return 1;
}

// Função para buscar o vértice com menor tempo em T
int buscaMenor(int* T, int* E, int n) {
    int menor = INT_MAX;
    int indice = -1;

    for (int i = 1; i <= n; i++) {
        if (E[i] != 0 && T[i] < menor) {
            menor = T[i];
            indice = i;
        }
    }
    return indice;
}

void rotaMaisRapida(int* T, int* E, int* partida, int* destino, int* tempos, int n) {
    for (int i = 1; i <= n; i++) {
        T[i] = INT_MAX;
        E[i] = i;
    }
    T[1] = 0;

    while (!isEmpty(E, n)) {
        int indiceV = buscaMenor(T, E, n);
        int v = E[indiceV];
        E[indiceV] = 0;

        for (int i = 1; i <= n; i++) {
            if (partida[i] == v && E[destino[i]] != 0) {
                int e = destino[i];

                if (T[e] > T[v] + tempos[i]) {
                    T[e] = T[v] + tempos[i];
                }
            }
        }
    }
}

int main() {
    FILE *file = fopen("arquivo.txt", "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int esquinaEntrega = 0;
    int qntdEsquinas = 0;

    fscanf(file, "%d", &esquinaEntrega);
    fscanf(file, "%d", &qntdEsquinas);

    // Definir o tamanho dos vetores
    int tamanho = 10; // Assumindo um tamanho máximo de 10 linhas
    int vetor1[tamanho];
    int vetor2[tamanho];
    int vetor3[tamanho];
    
    int i = 0;
    
    // Ler os dados do arquivo e armazená-los nos vetores
    while (i < tamanho && fscanf(file, "%d %d %d", &vetor1[i], &vetor2[i], &vetor3[i]) != EOF) {
        i++;
    }
    
    // Fechar o arquivo
    fclose(file);
    
    int T[qntdEsquinas];
    int E[qntdEsquinas];
    
    rotaMaisRapida(T, E, vetor1, vetor2, vetor3, qntdEsquinas);

    printf("Tempo mínimo para chegar na esquina %d: %d\n", esquinaEntrega, T[esquinaEntrega] );
    return 0;
}
