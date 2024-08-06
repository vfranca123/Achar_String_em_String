#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#ifndef Tempo_H
#define Tempo_H

typedef struct timeval timeval;
typedef struct rusage rusage;

void iniciar_contagem(struct timeval *ini_tempo_total, struct rusage *inicio);
void parar_contagem(struct timeval *fim_tempo_total, struct rusage *fim);
void printar_tempo_gasto(struct timeval *ini_tempo_total, struct rusage *inicio, struct timeval *fim_tempo_total, struct rusage *fim);
float diffUserTime(struct rusage *inicio, struct rusage *fim);
float diffSystemTime(struct rusage *inicio, struct rusage *fim);
float diffRealTime(struct timeval *inicio, struct timeval *fim);

#endif