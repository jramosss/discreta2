#include <stdio.h>
#include "../veinteveinte.h"
#include "parser.h"


/* ----- Color ----- */

char FijarColor(u32 x, u32 idx, Grafo G)
{
    Vert *vert = find_vert_by_index(idx, G);
    if (vert!=NULL){
        vert->color = x;
        return 0;
    } else {
        return 1;
    }
}

char FijarOrden(u32 i,Grafo G,u32 N){

    if (i < G->nvertices && N < G->nvertices){ //TODO no tendria que ser menor igual?
        G->vertices[i] = G->orden[N];
        G->vertices[i]->index = i;
        
        return 0;
    } else {
        return 1;
    }
}