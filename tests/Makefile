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
CHICOGRANDE 	= ../mains/main_chicogrande.c
GREEDY 			= ../mains/main_greedy.c
BIPARTITO 		= ../mains/main_bipartito.c
NUMCCS 			= ../mains/main_NumCCs.c
ALV				= ../mains/main_alv.c
SWITCH			= ../mains/main_switchcolores.c 
WP 				= ../mains/main_welshpowell.c
APROBACION		= ../mains/main_aprobacion.c

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

aprobacion:
	$(CC) $(CFLAGS0) $(TEST) $(APROBACION) $(OUT)

bipartito: 
	$(CC) $(CFLAGS0) $(TEST) $(BIPARTITO) $(OUT)

valgrind:
	valgrind --leak-check=full ./test < grafos/q7.txt

debug:
	$(CC) $(CFLAGS0) $(TEST_DEBUG) $(OUT)

clean:
	rm -rvf test

test_copiar:
	python test_copiar.py |  sed -i 's/[92//g' > results/copiar.txt

test_construccion:
	python test_construccion.py > results/construccion.txt

#Default 1000, hay que cambiarlo manualmente
test_aprobacion:
	python test_aprobacion.py 1000

test_alv:
	python test_alv.py

test_all:
	make test_copiar
	make test_construccion
	make test_aprobacion
	make test_alv