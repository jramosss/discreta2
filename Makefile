###################### MATEMÁTICA DISCRETA II ######################

######## Seteo básico. ########
CC = gcc -g
CFLAGS0 = -Wall -Wextra -std=c99 -Wpedantic -Wstrict-prototypes -Wunreachable-code -Wconversion -Wshadow
CFLAGS1 = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fstack-protector-strong
ALLFLAGS = $(CFLAGS0) $(CFLAGS1)

# Cambiar de acuerdo al directorio donde esté el código.
# Esto compila todos los .c menos los que empiecen con 'main'.
SOURCES_PATH = src/*.c
FUNCIONES_PATH = funciones/*.c	
SOURCES = $(filter-out $(wildcard main*.c), $(wildcard $(SOURCES_PATH)))
FUNCIONES = $(filter-out $(wildcard main*.c), $(wildcard $(FUNCIONES_PATH)))
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
SWITCH			= mains/main_switchcolores.c 
WP 				= mains/main_welshpowell.c
COPIAR 			= mains/main_copiar.c
FIJARPESO		=mains/main_fijarpeso.c
VECINOS			=mains/main_vecinos.c
BIPARTITO		=mains/main_bipartito.c

# Acá pueden configurar el nombre y directorio del output.
# Yo lo hago en el subdirectorio './bin/', y el archivo se llama 'out.o'.
OUT = -o test


######## Tipos de testeo. ########
TEST_NORMAL= -O3 $(SOURCES) $(FUNCIONES) $(NORMAL) 
TEST = -O3 $(SOURCES) $(FUNCIONES)
TEST_DEBUG= $(SOURCES) $(FUNCIONES) $(NORMAL) 


######## Opciones de la línea de comandos. ########
# Esto significa que 'make autodebug' compila en modo TEST_AUTODEBUG,
# 'make normal' en modo TEST_NORMAL y así. El comando 'make clean'
# borra todo lo que esté en el directorio de output y termine en '.o'.
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

fijarpeso:
	$(CC) $(CFLAGS0) $(TEST) $(FIJARPESO) $(OUT)

vecinos:
	$(CC) $(CFLAGS0) $(TEST) $(VECINOS) $(OUT)

bipartito:
	$(CC) $(CFLAGS0) $(TEST) $(BIPARTITO) $(OUT)

valgrind:
	valgrind --leak-check=full ./test < grafos/q7.txt

debug:
	$(CC) $(CFLAGS0) $(TEST_DEBUG) $(OUT)

clean:
	rm -rvf test
