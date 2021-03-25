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
#NORMAL = mainpulenta.c
NORMAL = mains/main_bip.c
DESAPROBACION = mains/main_desaprobacion.c

# Acá pueden configurar el nombre y directorio del output.
# Yo lo hago en el subdirectorio './bin/', y el archivo se llama 'out.o'.
OUT = -o ts


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

debug:
	$(CC) $(CFLAGS0) $(TEST_DEBUG) $(OUT)

clean:
	rm -rvf ts
