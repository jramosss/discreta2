#include <assert.h>
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
    u32 max = 0;                            //Minimo grado
    for(u32 i = 0; i < G->n; i++)
        if(G->vertices[i]->grado > max)
            max = G->vertices[i]->grado;

    return max;
}

/*------ Datos vertices ------*/

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

/*  
    Retorna el color del vecino numero j del vertice numero i en el orden 
    guardado en ese momento en G 
*/
u32 ColorVecino(u32 j, u32 i, Grafo G){
    if (i < G->n){
        Vert *vert = find_vert_by_index(i, G);
        return j < vert->grado ? vert->vecinos[j]->color : error;
    } 
    else
        return error;
}


/*  
    Retorna el nombre del vecino numero j del vertice numero i en el orden 
    guardado en ese momento en G 
*/
u32 NombreVecino(u32 j,u32 i,Grafo G){
    Vert *vert = find_vert_by_index(i, G);
    return vert == NULL ? (u32)error : vert->vecinos[j]->nombre;
}

/*  
    Devuelve el orden del vecino numero j del vertice numero i en el orden 
    guardado en ese momento en G 
*/
u32 OrdenVecino(u32 j,u32 i,Grafo G){
    Vert *vert = find_vert_by_index(i,G);
    return vert == NULL ? (u32)error : vert->vecinos[j]->index;
}
