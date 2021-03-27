#include "utils.h"
#include "../veinteveinte.h"


/* ----- Color ----- */

char FijarColor(u32 x, u32 idx, Grafo G)
{
    Vert *vert = find_vert_by_index(idx, G);
    if (vert!=NULL){
        vert->color = x;
        return '0';
    } 
    else return '1';
}

char FijarOrden(u32 i,Grafo G,u32 N){

    if (i < G->n && N < G->n){                      //? no tendria que ser menor igual?
        G->vertices[i] = G->orden_numerico[N];
        G->vertices[i]->index = i;
        
        return '0';
    } 
    else return '1';
}