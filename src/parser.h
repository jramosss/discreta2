#include "../RomaVictor.h"

Vert *vert_create (u32,u32);

Vert **parsear (FILE *fp, Grafo graph);

/**
 * Dado un grafo G y un grafo.txt se llena el arreglo de vertices y el natural
 * @param filename archivo que contiene el grafo
 * @param G grafo a completar
*/
void fill_verts(FILE *filename, Grafo G);

void num_lados_vertices (FILE *fp, Grafo g);