#include <stdio.h>
#include <stdlib.h>
#include "../RomaVictor.h"
#include "utils.h"
#include "cola.h"

struct Queue{
    u32 *datos;
    u32 inicio;
    u32 fin;
    u32 tam;
};


queue_t *createQueue(void) {
    queue_t *queue = (queue_t *)calloc(1, sizeof(queue_t));
    queue->tam = 0;
    queue->inicio = error;
    queue->fin = error;

    return queue;
}

char removeQueue(queue_t *queue) {
    free(queue->datos);
    free(queue);
    return 1;
}

u32 peek(queue_t *queue) {
    if (queue != NULL)
        return queue->datos[0];
    else
        return error;
}

char isEmpty(queue_t *queue) {
	if(queue->inicio == error || queue->inicio > queue->fin)
		return 1;
	else
		return 0;
}

/* Creo que esta funcion podria mejorar, tal vez teniendo claro los extremos no es necesario
hacer un while para llegar a la posicion donde se agrega el ultimo elemento */
void enqueue(u32 data, queue_t *queue) {
    queue->tam++;
    queue->datos = realloc(queue->datos, queue->tam * sizeof(u32));

    if(queue->inicio == error) {
        queue->inicio = 0;
        queue->fin = 0;
        queue->datos[queue->fin] = data;
    } else {
        queue->fin++;
        queue->datos[queue->fin] = data;
    }
}

u32 dequeue(queue_t *queue) {
    u32 elem_removido;
	if(queue->inicio == error || queue->inicio > queue->fin)
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	
	elem_removido = queue->datos[queue->inicio];
	queue->inicio = queue->inicio + 1;
	return elem_removido;
}

u32 getQueueSize(queue_t *queue) {
    return queue->tam;
}

// int main(void){
//     queue_t *cola = createQueue();
//     enqueue(10,cola);
//     enqueue(15,cola);
//     enqueue(20,cola);
//     enqueue(25,cola);
//     enqueue(30,cola);
//     printf("\nInicio: %u\n", cola->datos[cola->inicio]);
//     printf("\nFin: %u\n", cola->datos[cola->fin]);
//     printf("\nElemento removido %u\n", dequeue(cola));
//     printf("\nElemento removido %u\n", dequeue(cola));
//     printf("\nElemento removido %u\n", dequeue(cola));
//     printf("\nInicio: %u deberia ser 25\n", cola->datos[cola->inicio]);
//     enqueue(35, cola);
//     enqueue(40, cola);
//     enqueue(45, cola);
//     printf("\nInicio: %u\n", cola->datos[cola->inicio]);
//     printf("\nFin deberia ser 45: %u\n", cola->datos[cola->fin]);
// }