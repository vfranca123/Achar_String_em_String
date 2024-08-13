#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../interfaces/boyerMooreHorspool.h"
// Função para calcular a tabela de deslocamento
void calcular_tabela_deslocamento(char *padrao, int tamanho_padrao, int *tabela) {
    for (int i = 0; i < 256; i++) {
        tabela[i] = tamanho_padrao; // Inicializa com o tamanho do padrão
    }
    for (int i = 0; i < tamanho_padrao - 1; i++) {
        tabela[(unsigned char)padrao[i]] = tamanho_padrao - 1 - i;
    }
}

// Função que executa a busca utilizando Boyer-Moore-Horspool
bool busca_boyer_moore_horspool(char *texto, char *padrao, int a, int b) {
    int tamanho_texto = b - a + 1;
    int tamanho_padrao = strlen(padrao);

    if (tamanho_padrao > tamanho_texto) {
        return false;
    }

    int tabela[256];
    calcular_tabela_deslocamento(padrao, tamanho_padrao, tabela);

    int i = 0;
    while (i <= tamanho_texto - tamanho_padrao) {
        int j = tamanho_padrao - 1;
        while (j >= 0 && padrao[j] == texto[a + i + j]) {
            j--;
        }
        if (j < 0) {
            return true; // Padrão encontrado
        }
        i += tabela[(unsigned char)texto[a + i + tamanho_padrao - 1]];
    }

    return false; // Padrão não encontrado
}