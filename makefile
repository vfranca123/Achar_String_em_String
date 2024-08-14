# Alvo principal
all: tp3

# Cria o executável
tp3: obj/tp3.o obj/tempo.o obj/kmp.o obj/forcaBruta.o
	gcc obj/tp3.o obj/tempo.o obj/kmp.o obj/forcaBruta.o -o tp3

# Regras para criar arquivos objeto
obj/tp3.o: desenvolvimento_funcoes/tp3.c
	gcc -c desenvolvimento_funcoes/tp3.c -o obj/tp3.o

obj/tempo.o: desenvolvimento_funcoes/tempo.c interfaces/tempo.h
	gcc -c desenvolvimento_funcoes/tempo.c -o obj/tempo.o

obj/kmp.o: desenvolvimento_funcoes/kmp.c interfaces/kmp.h
	gcc -c desenvolvimento_funcoes/kmp.c -o obj/kmp.o

obj/forcaBruta.o: desenvolvimento_funcoes/forcaBruta.c interfaces/forcaBruta.h
	gcc -c desenvolvimento_funcoes/forcaBruta.c -o obj/forcaBruta.o

# Regra para limpar arquivos compilados
apagar:
	rm -f tp3 obj/*.o

