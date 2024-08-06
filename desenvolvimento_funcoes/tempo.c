#include "../interfaces/tempo.h"

void iniciar_contagem(struct timeval *ini_tempo_total, struct rusage *inicio){
    gettimeofday(ini_tempo_total, NULL);
    getrusage(RUSAGE_SELF, inicio);
}

void parar_contagem(struct timeval *fim_tempo_total, struct rusage *fim){
    getrusage(RUSAGE_SELF, fim);
    gettimeofday(fim_tempo_total, NULL);
}

void printar_tempo_gasto(struct timeval *ini_tempo_total, struct rusage *inicio, struct timeval *fim_tempo_total, struct rusage *fim) {
    printf("\nTempo total decorrido: %.06f segundos\n", diffRealTime(ini_tempo_total, fim_tempo_total));
    printf("Tempo de CPU: %.06f segundos\n", diffSystemTime(inicio, fim));
    printf("Tempo de usuário: %.06f segundos\n", diffUserTime(inicio, fim));
}

float diffUserTime(struct rusage *inicio, struct rusage *fim) {
    return (fim->ru_utime.tv_sec - inicio->ru_utime.tv_sec) +
        1e-6 * (fim->ru_utime.tv_usec - inicio->ru_utime.tv_usec);
}

float diffSystemTime(struct rusage *inicio, struct rusage *fim) {
    return (fim->ru_stime.tv_sec - inicio->ru_stime.tv_sec) +
        1e-6 * (fim->ru_stime.tv_usec - inicio->ru_stime.tv_usec);
}

float diffRealTime(struct timeval *inicio, struct timeval *fim) {
    return (fim->tv_sec - inicio->tv_sec) + (fim->tv_usec - inicio->tv_usec) / 1000000.0f;
}