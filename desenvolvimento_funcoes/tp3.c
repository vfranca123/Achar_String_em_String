#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "../interfaces/tempo.h"
#include "../interfaces/kmp.h"
#include "../interfaces/forcaBruta.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    struct timeval ini_tempo_total, fim_tempo_total;
    struct rusage inicio, fim;
    iniciar_contagem(&ini_tempo_total, &inicio);

    FILE *entrada = fopen(argv[1], "r");
    if (!entrada) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    // Abrir o arquivo de saída para escrita
    FILE *saida = fopen("saida.txt", "w");
    if (!saida) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(entrada);
        return 1;
    }
    
    FILE *saida2 = fopen("saida2.txt", "w");
    if (!saida2) {
        perror("Erro ao abrir o arquivo de saída 2");
        fclose(entrada);
        fclose(saida);
        return 1;
    }

    char *texto = NULL;
    char *padrao = NULL;
    size_t tamanho_texto = 0, tamanho_padro = 0;

    getline(&texto, &tamanho_texto, entrada);
    getline(&padrao, &tamanho_padro, entrada);

    // Remover o '\n' do final das strings, se presente
    texto[strcspn(texto, "\n")] = 0;
    padrao[strcspn(padrao, "\n")] = 0;

    int k;
    fscanf(entrada, "%d", &k);

    int *consultas = (int *)malloc(2 * k * sizeof(int));
    if (consultas == NULL) {
        perror("Erro ao alocar memória");
        fclose(entrada);
        fclose(saida);
        fclose(saida2);
        free(texto);
        free(padrao);
        return 1;
    }
    for (int i = 0; i < k; i++) {
        fscanf(entrada, "%d %d", &consultas[2 * i], &consultas[2 * i + 1]);
    }

    fclose(entrada);

    // Usar o método KMP para o primeiro arquivo de saída
    for (int i = 0; i < k; i++) {
        int a = consultas[2 * i] - 1;
        int b = consultas[2 * i + 1] - 1;
        if (a >= 0 && b < strlen(texto) && a <= b) {
            if (busca_kmp(texto, padrao, a, b)) {
                fprintf(saida, "sim\n");
            } else {
                fprintf(saida, "nao\n");
            }
        } else {
            fprintf(saida, "nao\n");
        }
    }

    // Usar o método de força bruta para o segundo arquivo de saída
    for (int i = 0; i < k; i++) {
        int a = consultas[2 * i] - 1;
        int b = consultas[2 * i + 1] - 1;
        if (a >= 0 && b < strlen(texto) && a <= b) {
            verificar_substring(texto, padrao, a, b, saida2);
        } else {
            fprintf(saida2, "nao\n");
        }
    }

    free(texto);
    free(padrao);
    free(consultas);

    parar_contagem(&fim_tempo_total, &fim);
    printar_tempo_gasto(&ini_tempo_total, &inicio, &fim_tempo_total, &fim);

    // Fechar os arquivos de saída
    fclose(saida);
    fclose(saida2);

    return 0;
}
