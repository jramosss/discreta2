#include "../../RomaVictor.h"

typedef struct Queue queue_t;

queue_t *createQueue(void);

char removeQueue(queue_t *);

// retorna valor de la cabeza, o -1 si esta vacia.
u32 peek(queue_t *);

char isEmpty(queue_t *);

char contains(queue_t*,u32);

// la cola tiene que ser distunsigned into de NULL.
void enqueue(u32, queue_t *);

// retorna -1 si la cola esta vacia.
u32 dequeue(queue_t *);

u32 getQueueSize(queue_t *);