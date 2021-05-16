#include "utils.h"
#include "../RomaVictor.h"
#include "../ADT/set/set.h"

char FijarColor(u32 x, u32 idx, Grafo G)
{
    Vert *vert = find_vert_by_index(idx, G);

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
    if (i >= G->n || j >= find_vert_by_index(i,G)->grado) return error;

    Vert *vert = find_vert_by_index(i,G);
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

static bool arrayIsPerm (u32* array, u32 N) {
    set_t* s = set_create();
    u32 max  = 0;

    for (u32 i = 0; i < N; i++) {
        set_insert(s,array[i]);
        if (array[i] > max)
            max = array[i];
    }

    //if (max != N) return 0;

    return set_length(s) == N;
}

char OrdenPorBloqueDeColores(Grafo G,u32* perm) {
    const u32 N = NumeroDeVertices(G);
    if (!arrayIsPerm(perm,N)) return false;

    return true;

}