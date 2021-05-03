#include "../RomaVictor.h"

Vert *vert_create (u32,u32);

Vert **parsear (FILE *fp, Grafo graph);

/**
 * Dado un grafo G y un grafo.txt se llena el arreglo de vertices y el natural
 * @param filename archivo que contiene el grafo
 * @param G grafo a completar
 * @return Devuelve 0 si habia la cantidad de lineas es >= a G->m, devuelve 1 si no se pasaron como minimo las m lineas requeridas.
*/
u32 fill_verts(FILE *filename, Grafo G);

u32 num_lados_vertices (FILE *fp, Grafo g);