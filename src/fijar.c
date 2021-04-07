#include "utils.h"
#include "../RomaVictor.h"

char FijarColor(u32 x, u32 idx, Grafo G)
{
    Vert *vert = find_vert_by_index(idx, G);

    if (vert==NULL) return '1';

    vert->color = x;
    return '0';
}

char FijarOrden(u32 i,Grafo G,u32 N){
    if (i >= G->n || N >= G->n) return '1';

    G->vertices[i] = G->orden_natural[N];
    G->vertices[i]->index = i;
    
    return '0';
}

u32 FijarPesoLadoConVecino(u32 j,u32 i,u32 p,Grafo G){
    // Ver que u32 debemos retornar, la funcion no aclara nada.
    if (i >= G->n || j >= find_vert_by_index(i,G)->grado) return error;

    Vert *vert = find_vert_by_index(i,G);
    vert->pesoslados[j] = p;
    return 0;
}