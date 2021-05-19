#include "utils.h"
#include "../RomaVictor.h"
#include "../ADT/set/set.h"

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

    if (max != N) return false;

    return set_length(s) == N;
}

char OrdenPorBloqueDeColores(Grafo G,u32* perm) {
    const u32 N = NumeroDeVertices(G);
    u32 max,c;
    max = c = 0;
    for (u32 i = 0; i < N; i++) {
        c = Color(i,G);
        if (c > max)
            max = c;
    }
    if (!arrayIsPerm(perm,max)) return false;
    //?
    lightVert** colorArray  = calloc(N,sizeof(u32));
    if (colorArray == NULL) return false;

    for (u32 i = 0; i < N; i++) {
        colorArray[i] = calloc(1,sizeof(lightVert));
        printf("Perm[%u]: %u\n",i,perm[i]);
        colorArray[i]->color = Color(perm[i],G);
        printf("color: %u\n",colorArray[i]->color);
        colorArray[i]->index = i;
    }

    printf("[");
    for (u32 i = 0; i < N; i++)
        printf(i == N-1 ? "%u" : "%u,",colorArray[i]->index);
    printf("]");

    qsort(colorArray,N,sizeof(u32),color_cmp);

    printf("[");
    for (u32 i = 0; i < N; i++)
        printf(i == N-1 ? "%u" : "%u,",colorArray[i]->index);
    printf("]");

    return true;
}