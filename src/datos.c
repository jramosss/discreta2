#include "utils.h"
#include "../RomaVictor.h"

/*------- Datos grafo -------*/

inline u32 NumeroDeVertices(Grafo G) {
    return G->n;
}

inline u32 NumeroDeLados(Grafo G) {
    return G->m;
}

inline u32 Delta(Grafo G) {
    return G->delta;            //Esto es por que opino que el delta deberia ser calculado en el parseo 
}

inline u32 Nombre(u32 i,Grafo G) {
    return G->vertices[i]->nombre;
}

inline u32 Color(u32 i,Grafo G){
    return G->vertices[i]->color;
}

inline u32 Grado(u32 i,Grafo G) {
    return G->vertices[i]->grado;
}

u32 ColorVecino(u32 j, u32 i, Grafo G){
    if (i >= G->n) return error;

    Vert *vert = G->vertices[i];
    return j < vert->grado ? vert->vecinos[j]->color : (u32)error;
}

u32 NombreVecino(u32 j,u32 i,Grafo G){
    if (i >= G->n) return error;

    Vert *vert = G->vertices[i];
    return j < vert->grado ? vert->vecinos[j]->nombre : (u32)error;
    //Checkear si vert == NULL aca seria una programacion mas defensiva
    //de lo necesario, ya que nunca andamos borrando vertices
}

u32 OrdenVecino(u32 j,u32 i,Grafo G){
    if (i >= G->n) return error;

    Vert *vert = G->vertices[i];
    return j < vert->grado ? vert->vecinos[j]->index : (u32)error; 
}

u32 PesoLadoConVecino(u32 j,u32 i,Grafo G){
    if (i >= G->n) return error;

    Vert *vert = G->vertices[i];
    return j < vert->grado ? vert->pesoslados[j] : (u32)error;
}