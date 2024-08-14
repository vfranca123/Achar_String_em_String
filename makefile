# Alvo principal
all: tp3

# Cria o executável
tp3: obj/tp3.o obj/tempo.o obj/kmp.o obj/forcaBruta.o
	gcc obj/tp3.o obj/tempo.o obj/kmp.o obj/forcaBruta.o -o tp3

# Regras para criar arquivos objeto
obj/tp3.o: desenvolvimento_funcoes/tp3.c | criar_obj_dir
	gcc -c desenvolvimento_funcoes/tp3.c -o obj/tp3.o

obj/tempo.o: desenvolvimento_funcoes/tempo.c interfaces/tempo.h | criar_obj_dir
	gcc -c desenvolvimento_funcoes/tempo.c -o obj/tempo.o

obj/kmp.o: desenvolvimento_funcoes/kmp.c interfaces/kmp.h | criar_obj_dir
	gcc -c desenvolvimento_funcoes/kmp.c -o obj/kmp.o

obj/forcaBruta.o: desenvolvimento_funcoes/forcaBruta.c interfaces/forcaBruta.h | criar_obj_dir
	gcc -c desenvolvimento_funcoes/forcaBruta.c -o obj/forcaBruta.o

# Regra para criar a pasta obj se ela não existir
criar_obj_dir:
	@mkdir -p obj

# Regra para limpar arquivos compilados
apagar:
	rm -f tp3 obj/*.o
