#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../veinteveinte.h"
#include "parser.h"

/*------- Datos grafo -------*/

u32 NumeroDeVertices(Grafo G) {
    return G->nvertices;
}

u32 NumeroDeLados(Grafo G) {
    return G->nlados;
}

u32 Delta(Grafo G) {
    u32 max = 0; //Minimo grado
    for(u32 i = 0; i < G->nvertices; i++)
        if(G->vertices[i]->grado > max)
            max = G->vertices[i]->grado;

    return max;
}

/*------ Datos vertices ------*/

Vert* find_vert_by_index (u32 i, Grafo graph)
{
    assert (i <= graph->nvertices);
    return graph->vertices[i];
}

u32 Nombre(u32 i,Grafo G) {
    return find_vert_by_index(i,G)->nombre;
}

u32 Color(u32 i,Grafo G){
    return find_vert_by_index(i,G)->color;
}

u32 Grado(u32 i,Grafo G) {
    return find_vert_by_index(i,G)->grado;
}

// Funciones de la seccion 9

/*  Devuelve el color del vecino numero j del vertice numero i en el orden 
    guardado en ese momento en G 
*/
u32 ColorVecino(u32 j, u32 i, Grafo g){
    if (i < g->nvertices){
        Vert *vert = find_vert_by_index(i, g);
        if(j < vert->grado){
            return vert->vecinos[j]->color;
        } else {
            return 4294967295;
        }
    } else {
        return 4294967295;
    }
}

u32 NombreVecino(u32 j,u32 i,Grafo G){
    Vert *vert = find_vert_by_index(i, G);
    return vert == NULL ? (u32)4294967295 : vert->vecinos[j]->nombre;
}

u32 OrdenVecino(u32 j,u32 i,Grafo G){
    Vert *vert = find_vert_by_index(i,G);
    return vert == NULL ? (u32)4294967295 : vert->vecinos[j]->index;
}
