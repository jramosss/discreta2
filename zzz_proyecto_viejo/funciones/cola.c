#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

typedef struct Node {
    struct Node *next;
    unsigned int data;
}node_t;

struct Queue{
    node_t *top;
    node_t *bottom;
    unsigned int size;
};

node_t *createNode(unsigned int data) {
    node_t *node = (node_t *) calloc (1, sizeof(node_t));
    node->data = data;
    node->next = NULL;

    return node;
}

char removeNode(node_t *node) {
    node->next = NULL;
    free(node);

    return (node == NULL);
}

queue_t *createQueue(void) {
    queue_t *queue = (queue_t *)calloc(1, sizeof(queue_t));

    return queue;
}

char removeQueue(queue_t *queue) {
    if(queue==NULL) return NULL;
    else if(isEmpty(queue)){
        free(queue);
        queue = NULL;
        return NULL;
    }
    node_t *ptr = queue->top;
    node_t *aux;

    while (ptr->next != NULL) {
        aux = ptr;
        ptr = ptr->next;

        removeNode(aux);
        queue->size--;
    }

    free(queue);

    return (queue == NULL);
}

unsigned int peek(queue_t *queue) {
    if (queue != NULL)
        return queue->top->data;
    else
        return 4294967295;
}

char isEmpty(queue_t *queue) {
    return (queue->top == NULL);
}

char contains (queue_t *q,unsigned int v){
    node_t* top = q->top;
    if((unsigned int)top->data == v)
        return 1;
    else{
        node_t* aux = q->top;
        while(aux != NULL) {
            if((unsigned int)aux->data == v){
                return 1;
            }
            aux = aux->next;
        }
    }
    return 0;
}


void enqueue(unsigned int data, queue_t *queue) {
    if (queue != NULL) {
        node_t *new = createNode(data);

        if (queue->top == NULL) {
            queue->top = new;
            queue->bottom = new;
        } else {
            node_t *ptr = queue->top;
            while (ptr != queue->bottom) {
                ptr = ptr->next;
            }
            ptr->next = new;
            new->next = NULL;
            queue->bottom = new;
        }

        queue->size++;
    }
}

unsigned int dequeue(queue_t *queue) {
    if (queue != NULL && queue->top != NULL) {
        unsigned int data;
        node_t *aux = queue->top;
        queue->top = aux->next;
        data = aux->data;
        removeNode(aux);

        queue->size--;
        return data;
    } else {
        return 4294967295;
    }
}

unsigned int getQueueSize(queue_t *queue) {
    return queue->size;
}
