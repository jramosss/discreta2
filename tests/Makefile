###################### MATEMÁTICA DISCRETA II ######################

######## Seteo básico. ########
CCPG = gcc -g -pg
CC = gcc -g
CFLAGS0 = -Wall -Wextra -std=c99 -Wpedantic -Wstrict-prototypes -Wunreachable-code -Wconversion -Wshadow
CFLAGS1 = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fstack-protector-strong
ALLFLAGS = $(CFLAGS0) $(CFLAGS1)

# Cambiar de acuerdo al directorio donde esté el código.
# Esto compila todos los .c menos los que empiecen con 'main'.
SOURCES_PATH   = ../src/*.c
QUEUE_PATH 	   = ../ADT/queue/*.c
HASH_PATH 	   = ../ADT/hash/*.c
SET_PATH 	   = ../ADT/set/*.c

SOURCES   = $(filter-out $(wildcard main*.c), $(wildcard $(SOURCES_PATH)))
QUEUE     = $(filter-out $(wildcard main*.c), $(wildcard $(QUEUE_PATH)))
HASH      = $(filter-out $(wildcard main*.c), $(wildcard $(HASH_PATH)))
SET       = $(filter-out $(wildcard main*.c), $(wildcard $(SET_PATH)))

NORMAL 			= ../mains/main.c
COPIAR 			= ../mains/main_copiar.c
CONSTRUCCION 	= ../mains/main_construccion.c
APROBACION 		= ../mains/main_aprobacion.c
CHICOGRANDE 	= ../mains/main_chicogrande.c
GREEDY 			= ../mains/main_greedy.c
BIPARTITO 		= ../mains/main_bipartito.c
NUMCCS 			= ../mains/main_NumCCs.c
ALV				= ../mains/main_alv.c
ALV2			= ../mains/main_alv2.c
SWITCH			= ../mains/main_switchcolores.c 
WP 				= ../mains/main_welshpowell.c
COPIAR 			= ../mains/main_copiar.c
FIJARPESO		= ../mains/main_fijarpeso.c
VECINOS			= ../mains/main_vecinos.c
BIPARTITO		= ../mains/main_bipartito.c
ORDEN			= ../mains/main_orden.c

OUT = -o test
LEAK_TESTING_GRAPH = grafos/q7.txt

TEST = -O3 $(SOURCES) $(FUNCIONES) $(HASH) $(QUEUE) $(SET)

######## Opciones de la línea de comandos. ########

.PHONY: normal

normal:
	$(CC) $(CFLAGS0) $(TEST) $(NORMAL) $(OUT)

aprobacion:
	$(CC) $(CFLAGS0) $(TEST)   $(APROBACION) $(OUT)

cg:
	$(CC) $(CFLAGS0) $(TEST)   $(CHICOGRANDE) $(OUT)

bip:
	$(CC) $(CFLAGS0) $(TEST)   $(BIPARTITO) $(OUT)

nc:
	$(CC) $(CFLAGS0) $(TEST)   $(NUMCCS) $(OUT)

alv:
	$(CC) $(CFLAGS0) $(TEST)   $(ALV) $(OUT)

alv2:
	$(CC) $(CFLAGS0) $(TEST)   $(ALV2) $(OUT)

sc:
	$(CC) $(CFLAGS0) $(TEST)   $(SWITCH) $(OUT)

wp:
	$(CC) $(CFLAGS0) $(TEST)   $(WP) $(OUT)

list:
	echo "cg,greedy,bip,nc,alv,sc,wp,debug,clean"

copiar:
	$(CC) $(CFLAGS0) $(TEST)   $(COPIAR) $(OUT)

construccion:
	$(CC) $(CFLAGS0) $(TEST)   $(CONSTRUCCION) $(OUT)

fijarpeso:
	$(CC) $(CFLAGS0) $(TEST)   $(FIJARPESO) $(OUT)

bipartito:
	$(CC) $(CFLAGS0) $(TEST)   $(BIPARTITO) $(OUT)

greedy:
	$(CC) $(CFLAGS0) $(TEST)   $(GREEDY) $(OUT)

orden:
	$(CC) $(CFLAGS0) $(TEST)  $(ORDEN) $(OUT)

valgrind:
	valgrind --leak-check=full ./test < $(LEAK_TESTING_GRAPH)

leak_bipartito:
	echo LEAK CHECK BIPARTITO
	make bipartito
	make valgrind

leak_construccion:
	echo LEAK CHECK CONSTRUCCION
	make construccion
	make valgrind

leak_greedy:
	echo LEAK CHECK GREEDY
	make greedy
	make valgrind

leak_copiar:
	echo LEAK CHECK COPIAR
	make copiar
	make valgrind

leak_all:
	make leak_bipartito
	make leak_construccion
	make leak_greedy

gprof_greedy:
	$(CC) -pg $(CFLAGS0) $(TEST) $(APROBACION) $(OUT)
	./test 1000 < grafos/Octo
	gprof ./test gmon.out > analisis.txt

gprof_alv:
	$(CC) -pg $(CFLAGS0) $(TEST) $(ALV) $(OUT)
	./test 1000 < grafos/Octo
	gprof ./test gmon.out > analisis.txt

clean:
	rm -rvf test
