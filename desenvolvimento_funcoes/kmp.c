#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../interfaces/kmp.h"


void calcular_array_lps(const char *padrao, int tamanho_padro, int *array_lps) {
    int comprimento_prefixo = 0;
    array_lps[0] = 0;
    int indice = 1;

    while (indice < tamanho_padro) {
        if (padrao[indice] == padrao[comprimento_prefixo]) {
            comprimento_prefixo++;
            array_lps[indice] = comprimento_prefixo;
            indice++;
        } else {
            if (comprimento_prefixo != 0) {
                comprimento_prefixo = array_lps[comprimento_prefixo - 1];
            } else {
                array_lps[indice] = 0;
                indice++;
            }
        }
    }
}

int busca_kmp(const char *texto, const char *padrao, int inicio, int fim) {
    int tamanho_texto = fim - inicio + 1;
    int tamanho_padro = strlen(padrao);
    int *array_lps = (int *)malloc(sizeof(int) * tamanho_padro);
    int indice_texto = inicio;
    int indice_padro = 0;

    calcular_array_lps(padrao, tamanho_padro, array_lps);

    while (indice_texto <= fim) {
        if (padrao[indice_padro] == texto[indice_texto]) {
            indice_padro++;
            indice_texto++;
        }

        if (indice_padro == tamanho_padro) {
            free(array_lps);
            return 1; // Padrão encontrado
        } else if (indice_texto <= fim && padrao[indice_padro] != texto[indice_texto]) {
            if (indice_padro != 0) {
                indice_padro = array_lps[indice_padro - 1];
            } else {
                indice_texto++;
            }
        }
    }

    free(array_lps);
    return 0; // Padrão não encontrado
}