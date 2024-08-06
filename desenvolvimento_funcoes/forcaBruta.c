#include <stdio.h>
#include <string.h>
#include "../interfaces/forcaBruta.h"

void verificar_substring(const char *texto, const char *padrao, int inicio, int fim, FILE *saida) {
    int tamanho_padro = strlen(padrao);
    int tamanho_texto = fim - inicio + 1;

    if (tamanho_padro > tamanho_texto) {
        fprintf(saida, "nao\n");
        return;
    }

    for (int i = 0; i <= tamanho_texto - tamanho_padro; i++) {
        int j;
        for (j = 0; j < tamanho_padro; j++) {
            if (texto[inicio + i + j] != padrao[j]) {
                break;
            }
        }
        if (j == tamanho_padro) {
            fprintf(saida, "sim\n");
            return;
        }
    }
    fprintf(saida, "nao\n");
}
