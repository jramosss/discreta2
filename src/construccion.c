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

void DestruccionDelGrafo(Grafo G) {
    for (u32 i = 0; i < G->n; i++) {
        free(G->vertices[i]->vecinos);
        free(G->vertices[i]);
    }

    free(G->orden_natural);
    free(G->vertices);
    free(G->raiz);
    free(G);
}

Grafo CopiarGrafo(Grafo G) {
    
    Grafo C = calloc(1, sizeof(Grafo));
    C->n = NumeroDeVertices(G);
    C->m = NumeroDeLados(G);
    C->delta = Delta(G);
    C->orden_natural = calloc(C->n, sizeof(Vert*));
    C->vertices = calloc(C->n, sizeof(Vert*));
};
