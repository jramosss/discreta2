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

char OrdenPorBloqueDeColores(Grafo G, u32* perm) {
    const u32 N = NumeroDeVertices(G);
    u32 max,c,sum_colores;
    max = c = sum_colores = 0;
    u32 cant_colores = sizeof(perm)/sizeof(perm[0]);

    for (u32 i = 0; i < N; i++) {
        for (u32 j = 0; j < cant_colores-1; j++) {
            if (i == 0) 
                sum_colores += perm[j];
            if (perm[j] > Color(i,G))                    // La permutacion tiene colores que el grafo no.
                return false;
        }
        if (i == 0 && sum_colores != ((cant_colores-1)*cant_colores)/2) {       // Si esto sucede significa que no es una permutacion
            return false;
        }
    }
    
    return true;
}