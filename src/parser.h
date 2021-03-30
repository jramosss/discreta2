#include "../veinteveinte.h"
#define MAXCHAR 100000

Vert *vert_create (u32 name, u32 mlados);

Vert **parsear (FILE *fp, Grafo graph);

/**
 * Dado un grafo G y un grafo.txt se llena el arreglo de vertices y el natural
 * @param filename archivo que contiene el grafo
 * @param G grafo a completar
*/
void fill_verts(FILE *filename, Grafo G);

void num_lados_vertices (FILE *fp, Grafo g);