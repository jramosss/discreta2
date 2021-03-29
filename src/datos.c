#include "utils.h"
#include "../veinteveinte.h"

/*------- Datos grafo -------*/

u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

u32 NumeroDeLados(Grafo G) {
    return G->m;
}

u32 Delta(Grafo G) {
    return G->delta;            //Esto es por que opino que el delta deberia ser calculado en el parseo 
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

u32 ColorVecino(u32 j, u32 i, Grafo G){
    if (i >= G->n) return error;

    Vert *vert = find_vert_by_index(i, G);
    return j < vert->grado ? vert->vecinos[j]->color : (u32)error;
}

u32 NombreVecino(u32 j,u32 i,Grafo G){
    if (i >= G->n) return error;

    Vert *vert = find_vert_by_index(i, G);
    return j < vert->grado ? vert->vecinos[j]->nombre : (u32)error;
    //Checkear si vert == NULL aca seria una programacion mas defensiva
    //de lo necesario, ya que nunca andamos borrando vertices
}

u32 OrdenVecino(u32 j,u32 i,Grafo G){
    if (i >= G->n) return error;

    Vert *vert = find_vert_by_index(i,G);
    return j < vert->grado ? vert->vecinos[j]->index : (u32)error; 
}
