###################### MATEMÁTICA DISCRETA II ######################

######## Seteo básico. ########
CC = gcc -g
CFLAGS0 = -Wall -Wextra -std=c99 -Wpedantic -Wstrict-prototypes -Wunreachable-code -Wconversion -Wshadow
CFLAGS1 = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fstack-protector-strong
ALLFLAGS = $(CFLAGS0) $(CFLAGS1)

# Cambiar de acuerdo al directorio donde esté el código.
# Esto compila todos los .c menos los que empiecen con 'main'.
SOURCES_PATH   = src/*.c
QUEUE_PATH 	   = ADT/queue/*.c
HASH_PATH 	   = ADT/hash/*.c
SET_PATH 	   = ADT/set/*.c

SOURCES = $(filter-out $(wildcard main*.c), $(wildcard $(SOURCES_PATH)))
QUEUE     = $(filter-out $(wildcard main*.c), $(wildcard $(QUEUE_PATH)))
HASH      = $(filter-out $(wildcard main*.c), $(wildcard $(HASH_PATH)))
SET       = $(filter-out $(wildcard main*.c), $(wildcard $(SET_PATH)))
# Acá yo tengo un directorio 'mains', donde tengo varios mains.
# El normal testea cosas parecidas a las del profe, el debug
# es más riguroso pero no sirve para medir tiempos ni uso
# de memoria. Pueden hacer tantos como gusten y agregarlos acá.
# Reemplacen los paths de acuerdo a donde uds guarden sus mains.

#Reemplazar dependiendo del main que desean usar, para tests.sh solo main.c
NORMAL 			= mains/main.c
COPIAR 			= mains/main_copiar.c
CONSTRUCCION 	= mains/main_construccion.c
DESAPROBACION 	= mains/main_desaprobacion.c
CHICOGRANDE 	= mains/main_chicogrande.c
GREEDY 			= mains/main_greedy.c
BIPARTITO 		= mains/main_bipartito.c
NUMCCS 			= mains/main_NumCCs.c
ALV				= mains/main_alv.c
ALV2			= mains/main_alv2.c
SWITCH			= mains/main_switchcolores.c 
WP 				= mains/main_welshpowell.c
COPIAR 			= mains/main_copiar.c
FIJARPESO		= mains/main_fijarpeso.c
VECINOS			= mains/main_vecinos.c
BIPARTITO		= mains/main_bipartito.c
ORDEN			= mains/main_orden.c

# Acá pueden configurar el nombre y directorio del output.
# Yo lo hago en el subdirectorio './bin/', y el archivo se llama 'out.o'.
OUT = -o test
LEAK_TESTING_GRAPH = grafos/q7.txt


######## Tipos de testeo. ########
TEST_NORMAL= -O3 $(SOURCES) $(FUNCIONES) $(NORMAL) 
TEST = -O3 $(SOURCES) $(FUNCIONES) $(HASH)
TEST_DEBUG= $(SOURCES) $(FUNCIONES) $(NORMAL) 


######## Opciones de la línea de comandos. ########
# Esto significa que 'make autodebug' compila en modo TEST_AUTODEBUG,
# 'make normal' en modo TEST_NORMAL y así. El comando 'make clean'
# borra todo lo que esté en el directorio de output y termine en '.o'.
.PHONY: normal

normal:
	$(CC) $(CFLAGS0) $(TEST_NORMAL) $(OUT)

desaprobacion:
	$(CC) $(CFLAGS0) $(TEST) $(QUEUE)  $(SET)  $(DESAPROBACION) $(OUT)

cg:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(CHICOGRANDE) $(OUT)

bip:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(BIPARTITO) $(OUT)

nc:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(NUMCCS) $(OUT)

alv:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(ALV) $(OUT)

alv2:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(ALV2) $(OUT)

sc:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(SWITCH) $(OUT)

wp:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(WP) $(OUT)

list:
	echo "cg,greedy,bip,nc,alv,sc,wp,debug,clean"

copiar:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(COPIAR) $(OUT)

construccion:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(CONSTRUCCION) $(OUT)

fijarpeso:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(FIJARPESO) $(OUT)

bipartito:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(BIPARTITO) $(OUT)
greedy:
	$(CC) $(CFLAGS0) $(TEST)  $(QUEUE)  $(SET) $(GREEDY) $(OUT)

orden:
	$(CC) $(CFLAGS0) $(TEST) $(QUEUE)  $(SET) $(ORDEN) $(OUT)

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
	make leak_copiar

debug:
	$(CC) $(CFLAGS0) $(TEST_DEBUG) $(OUT)

clean:
	rm -rvf test
