CC = gcc -g
CFLAGS0 = -Wall -Wextra -std=c99 -Wpedantic -Wstrict-prototypes -Wunreachable-code -Wconversion -Wshadow
CFLAGS1 = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fstack-protector-strong
ALLFLAGS = $(CFLAGS0) $(CFLAGS1)

# Cambiar de acuerdo al directorio donde esté el código.
# Esto compila todos los .c menos los que empiecen con 'main'.
SOURCES_PATH = ../src/*.c
FUNCIONES_PATH = ../funciones/*.c	
SOURCES = $(filter-out $(wildcard main*.c), $(wildcard $(SOURCES_PATH)))
FUNCIONES = $(filter-out $(wildcard main*.c), $(wildcard $(FUNCIONES_PATH)))

NORMAL 			= ../mains/main.c
COPIAR 			= ../mains/main_copiar.c
CONSTRUCCION 	= ../mains/main_construccion.c
BIP 			= ../mains/main_bip.c
DESAPROBACION 	= ../mains/main_desaprobacion.c
CHICOGRANDE 	= ../mains/main_for_chicogrande.c
GREEDY 			= ../mains/main_greedy.c
BIPARTITO 		= ../mains/main_for_bipartito.c
NUMCCS 			= ../mains/main_for_NumCCs.c
ALV				= ../mains/main_for_aleatvert.c
SWITCH			= ../mains/main_for_switchcolores.c 
WP 				= ../mains/main_for_welshpowell.c

OUT = -o test


######## Tipos de testeo. ########
TEST_NORMAL= -O3 $(SOURCES) $(FUNCIONES) $(NORMAL) 
TEST = -O3 $(SOURCES) $(FUNCIONES)
TEST_DEBUG= $(SOURCES) $(FUNCIONES) $(NORMAL) 

.PHONY: normal

normal:
	$(CC) $(CFLAGS0) $(TEST_NORMAL) $(OUT)

desaprobacion:
	$(CC) $(CFLAGS0) $(TEST) $(DESAPROBACION) $(OUT)

cg:
	$(CC) $(CFLAGS0) $(TEST) $(CHICOGRANDE) $(OUT)

greedy:
	$(CC) $(CFLAGS0) $(TEST) $(GREEDY) $(OUT)

bip:
	$(CC) $(CFLAGS0) $(TEST) $(BIPARTITO) $(OUT)

nc:
	$(CC) $(CFLAGS0) $(TEST) $(NUMCCS) $(OUT)

alv:
	$(CC) $(CFLAGS0) $(TEST) $(ALV) $(OUT)

sc:
	$(CC) $(CFLAGS0) $(TEST) $(SWITCH) $(OUT)

wp:
	$(CC) $(CFLAGS0) $(TEST) $(WP) $(OUT)

list:
	echo "cg,greedy,bip,nc,alv,sc,wp,debug,clean"

copiar:
	$(CC) $(CFLAGS0) $(TEST) $(COPIAR) $(OUT)

construccion:
	$(CC) $(CFLAGS0) $(TEST) $(CONSTRUCCION) $(OUT)

valgrind:
	valgrind --leak-check=full ./test < grafos/q7.txt

debug:
	$(CC) $(CFLAGS0) $(TEST_DEBUG) $(OUT)

clean:
	rm -rvf test

test_copiar:
	python3 test_copiar.py |  sed -i 's/[92//g' > results/copiar.txt
	cd ..

test_construccion:
	python3 test_construccion.py > results/construccion.txt

test_all:
	make test_copiar
	make test_construccion