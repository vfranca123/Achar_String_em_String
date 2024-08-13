all: obj/tp3.o obj/tempo.o obj/Kmp.o obj/forcaBruta.o obj/boyerMooreHorspool.o
	gcc obj/tp3.o obj/tempo.o obj/Kmp.o obj/forcaBruta.o obj/boyerMooreHorspool.o -o tp3

obj/tp3.o: desenvolvimento_funcoes/tp3.c
	gcc desenvolvimento_funcoes/tp3.c -c
	mv tp3.o obj/

obj/tempo.o: desenvolvimento_funcoes/tempo.c interfaces/tempo.h
	gcc desenvolvimento_funcoes/tempo.c -c
	mv tempo.o obj/

obj/Kmp.o: desenvolvimento_funcoes/kmp.c interfaces/kmp.h
	gcc desenvolvimento_funcoes/kmp.c -c
	mv kmp.o obj/

obj/forcaBruta.o: desenvolvimento_funcoes/forcaBruta.c interfaces/forcaBruta.h
	gcc desenvolvimento_funcoes/forcaBruta.c -c
	mv forcaBruta.o obj/

obj/boyerMooreHorspool.o: desenvolvimento_funcoes/boyerMooreHorspool.c interfaces/boyerMooreHorspool.h
	gcc desenvolvimento_funcoes/boyerMooreHorspool.c -c
	mv boyerMooreHorspool.o obj/

apagar:
	rm tp3 obj/*.o
