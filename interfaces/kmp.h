#ifndef KMP_H
#define KMP_H
void calcular_array_lps(const char *padrao, int tamanho_padro, int *array_lps);
int busca_kmp(const char *texto, const char *padrao, int inicio, int fim);

#endif 