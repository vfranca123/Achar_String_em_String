#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "../interfaces/tempo.h"
#include "../interfaces/kmp.h"
#include "../interfaces/forcaBruta.h"
#include "../interfaces/boyerMooreHorspool.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <algoritmo_a_ser_usado> <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    struct timeval ini_tempo_total, fim_tempo_total;
    struct rusage inicio, fim;
    iniciar_contagem(&ini_tempo_total, &inicio);

    FILE *entrada = fopen(argv[2], "r");
    if (!entrada) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    // Abrir os arquivos de saída para escrita
    FILE *saida = fopen("saida.txt", "w");
    if (!saida) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(entrada);
        return 1;
    }
    
    

    char *texto = NULL;
    char *padrao = NULL;
    size_t tamanho_texto = 0, tamanho_padro = 0;

    getline(&texto, &tamanho_texto, entrada);
    getline(&padrao, &tamanho_padro, entrada);

    texto[strcspn(texto, "\n")] = 0;
    padrao[strcspn(padrao, "\n")] = 0;

    int k;
    fscanf(entrada, "%d", &k);

    int *consultas = (int *)malloc(2 * k * sizeof(int));
    if (consultas == NULL) {
        perror("Erro ao alocar memória");
        fclose(entrada);
        fclose(saida);
        free(texto);
        free(padrao);
        return 1;
    }
    for (int i = 0; i < k; i++) {
        fscanf(entrada, "%d %d", &consultas[2 * i], &consultas[2 * i + 1]);
    }

    fclose(entrada);

    // Escolher o algoritmo com base no segundo argumento
    if (strcmp(argv[1], "kmp") == 0 || strcmp(argv[1], "KMP") == 0) {
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
    }
    if (strcmp(argv[1], "forca") == 0 || strcmp(argv[1], "FORCA") == 0) {
        for (int i = 0; i < k; i++) {
            int a = consultas[2 * i] - 1;
            int b = consultas[2 * i + 1] - 1;
            if (a >= 0 && b < strlen(texto) && a <= b) {
                verificar_substring(texto, padrao, a, b, saida);
            } else {
                fprintf(saida, "nao\n");
            }
        }
    } 
    if (strcmp(argv[1], "bm_horspool") == 0 || strcmp(argv[1], "BM_HORSPOOL") == 0) {
        for (int i = 0; i < k; i++) {
            int a = consultas[2 * i] - 1;
            int b = consultas[2 * i + 1] - 1;
            if (a >= 0 && b < strlen(texto) && a <= b) {
                if (busca_boyer_moore_horspool(texto, padrao, a, b)) {
                    fprintf(saida, "sim\n");
                } else {
                    fprintf(saida, "nao\n");
                }
            } else {
                fprintf(saida, "nao\n");
            }
        }
    } 
 

    free(texto);
    free(padrao);
    free(consultas);

    parar_contagem(&fim_tempo_total, &fim);
    printar_tempo_gasto(&ini_tempo_total, &inicio, &fim_tempo_total, &fim);

    fclose(saida);
    

    return 0;
}
