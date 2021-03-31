#include <stdlib.h>
#include "../RomaVictor.h"
#include "parser.h"


Grafo ConstruccionDelGrafo (void)
{   
    Grafo G = calloc(1, sizeof(GrafoSt));
    num_lados_vertices(stdin, G);
    G->raiz = NULL;
    G->delta = 0;
    G->orden_natural = calloc(G->n + 1, sizeof(Vert*));         // Agregamos una posicion para el ultimo vertice.
    G->vertices = calloc(G->n, sizeof(Vert*));
    fill_verts(stdin, G);
    
    return G;
}