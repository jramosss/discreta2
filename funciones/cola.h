#ifndef RAMOS_BERNARDI_PALUDI
#define RAMOS_BERNARDI_PALUDI

typedef struct Queue queue_t;

queue_t *createQueue(void);

char removeQueue(queue_t *);

// retorna valor de la cabeza, o -1 si esta vacia.
unsigned int peek(queue_t *);

char isEmpty(queue_t *);

char contains(queue_t*,unsigned int);

// la cola tiene que ser distunsigned into de NULL.
void enqueue(unsigned int, queue_t *);

// retorna -1 si la cola esta vacia.
unsigned int dequeue(queue_t *);

unsigned int getQueueSize(queue_t *);

#endif  // RAMOS_BERNARDI_PALUDI
