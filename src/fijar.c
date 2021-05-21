#include "utils.h"
#include "../RomaVictor.h"
#include "../ADT/set/set.h"
#include "../ADT/queue/cola.h"

char FijarColor(u32 x, u32 idx, Grafo G)
{
    Vert *vert = G->vertices[idx];

    if (vert==NULL) return 1;

    vert->color = x;
    return 0;
}

char FijarOrden(u32 i,Grafo G,u32 N){
    if (i >= G->n || N >= G->n) return 1;
    
    G->vertices[i] = G->orden_natural[N];
    G->vertices[i]->index = i;

    return 0;
}

u32 FijarPesoLadoConVecino(u32 j,u32 i,u32 p,Grafo G){
    // Ver que u32 debemos retornar, la funcion no aclara nada.
    Vert *vert = G->vertices[i];
    if (i >= G->n || j >= vert->grado) return error;

    vert->pesoslados[j] = p;

    return 0;
}

char AleatorizarVertices(Grafo G, u32 R) {
    const u32 N = NumeroDeVertices(G);
    u32 *guia   = malloc(N*sizeof(u32));    // Usamos este arreglo de guia para ordenar los vertices
    if (guia == NULL) return 1;
    
    for (u32 i = 0; i < N; i++)
        guia[i] = i;                        

    srand(R);
    for (u32 i = N-1; i > 0; i--) {
        swap(&guia[i],&guia[(u32)rand() % (i+1)]);
        FijarOrden(i,G,guia[i]);
    }

    FijarOrden(0,G,guia[0]);

    free(guia);

    return 0;
}

static char arrayIsPerm (u32* array, u32 N) {
    set_t* s = set_create();
    u32 max  = 0;

    for (u32 i = 0; i < N; i++) {
        set_insert(s,array[i]);
        if (array[i] > max)
            max = array[i];
    }

    if (max+1 != N) return false;

    const char lenIsEqual = set_length(s) == N;

    free(s);

    return lenIsEqual;
}

char OrdenPorBloqueDeColores(Grafo G,u32* perm) {
    const u32 N = NumeroDeVertices(G);
    u32 max,c;
    max = c = 0;
    for (u32 i = 0; i < N; i++) {
        c = Color(i,G);
        if (c > max)
            max = c;
        FijarOrden(i, G, i);
    }
    if (!arrayIsPerm(perm,max)) return 0;
    
    queue_t **queue = calloc(max + 1, sizeof(queue_t *));
    
    for (u32 i = 0; i < N; i++) {
        if (queue[Color(i,G)] == NULL)
            queue[Color(i,G)] = createQueue();

        enqueue(i, queue[Color(i,G)]);
    }

    u32 j = 0;
    for (u32 i = 0; i < max + 1; i++) {
        while (!isEmpty(queue[i])) {
            FijarOrden(j, G, dequeue(queue[i]));
            j++;
        }
    }

    for (u32 i = 0; i < max+1; i++)
        removeQueue(queue[i]);

    free(queue);

    return 1;
}