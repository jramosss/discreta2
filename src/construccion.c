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

static Vert* copy_vert_aux (u32 nombre, u32 index, u32 color, u32 grado) {
    Vert* b    = vert_create(nombre,index);
    b->color   = color;
    b->grado   = grado;
    b->vecinos = calloc(grado,sizeof(Vert*));

    return b;
}

/* Copia los vecinos del vertice v al vertice b */
static void copy_vecinos (Vert* v,Vert* b,Grafo C) {
    for (u32 i = 0; i < v->grado; i++) {
        if (!C->orden_natural[v->vecinos[i]->index]){
            Vert* vec = v->vecinos[i];
            C->vertices[vec->index] = copy_vert_aux(vec->nombre,vec->index,vec->color,vec->grado);
            C->orden_natural[vec->index] = C->vertices[vec->index];
            b->vecinos[i] = C->vertices[vec->index];
        }
        else
            b->vecinos[i] = C->orden_natural[v->vecinos[i]->index];
    }
}

static Vert* vert_copy (Vert* v, Grafo C) {
    Vert* b    = vert_create(v->nombre,v->index);
    b->color   = v->color;
    b->grado   = v->grado;
    b->index   = v->index;
    b->nombre  = v->nombre;
    b->vecinos = calloc(b->grado, sizeof(Vert*));
    copy_vecinos(v,b,C);

    return b;
}

Grafo CopiarGrafo (Grafo G) {
    Grafo C             = (Grafo)calloc(1,sizeof(GrafoSt));
    C->n                = G->n;
    C->m                = G->m;
    C->delta            = G->delta;
    C->vertices         = calloc(C->n, sizeof(Vert *));
    C->orden_natural    = calloc(C->n, sizeof(Vert *));
    if (C == NULL || C->vertices == NULL || C->orden_natural == NULL) return NULL;

    for (u32 i = 0; i < G->n; i++) {
        if (!C->vertices[i]) {
            C->vertices[i]      = vert_copy(G->vertices[i], C);
            C->orden_natural[i] = C->vertices[i];
        } else
            copy_vecinos(G->vertices[i], C->vertices[i], C);
    }

    return C;
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
