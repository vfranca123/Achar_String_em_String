#ifndef boyerMooreHorspool_H
#define boyerMooreHorspool_H

void calcular_tabela_deslocamento(char *padrao, int tamanho_padrao, int *tabela);
bool busca_boyer_moore_horspool(char *texto, char *padrao, int a, int b);

#endif 