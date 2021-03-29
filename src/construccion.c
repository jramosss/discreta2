#include "../veinteveinte.h";

void DestruccionDelGrafo(Grafo G) {
    for (u32 i = 0; i < G->n; i++) {
        free(G->vertices[i]->vecinos);
        free(G->vertices[i]);
    }

    free(G->orden);
    free(G->vertices);
    free(G->raiz);
    free(G);
}

Vert* CopiarVertice(Vert V) {
    Vert C = calloc()
}

Grafo CopiarGrafo(Grafo G) {
    
    Grafo C = calloc(1, sizeof(Grafo));
    C->n = NumeroDeVertices(G);
    C->m = NumeroDeLados(G);
    C->delta = Delta(G);
    C->orden = calloc(C->n, sizeof(Vert*));
    C->vertices = calloc(C->n, sizeof(Vert*));
};