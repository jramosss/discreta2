#include <assert.h>
#include<stdio.h>
#include<stdlib.h>
#include "../veinteveinte.h"
#include "parser.h"

static int compare(const void *x, const void *y){
    Vert *xs = *(struct Vert **)x;
    Vert *ys = *(struct Vert **)y;
    return (int)(xs->nombre - ys->nombre);
}

static void copy_array_of_vert(Grafo g){
    for (u32 i = 0; i < g->nvertices; i++) {
        g->orden[i] = g->vertices[i];
    }
}

Grafo ConstruccionDelGrafo (void)
{   
    Grafo G = calloc(1, sizeof(GrafoSt));
    G->raiz = NULL;
    G->parseo = array_of_tuples(stdin,G);
    G->vertices = calloc(G->nvertices, sizeof(Vert*));
    G->orden = calloc(G->nvertices, sizeof(Vert*));
    graph_fill(G); // Corroborar que haya luego del numero m en el documento, m lineas. De lo contrario devolver NULL.
    fill_vecinos(G);
    copy_array_of_vert(G);
    G->delta = Delta(G);
    qsort(G->orden, G->nvertices, sizeof(Vert *), &compare);
    free(G->parseo);
    Greedy(G);
    return G;
}

/*---------- Auxiliares para destruccion de grafo ------------- */

static void liberar_arbol(Vert* raiz){
    if(raiz != NULL){
        liberar_arbol(raiz->vert_de);
        liberar_arbol(raiz->vert_iz);
        free(raiz);
    }
}

static void liberar_orden(Grafo g)
{
    for (u32 j = 0 ; j < g->nvertices ; j++)
    {
        g->vertices[j] = NULL;
        g->orden[j] = NULL;
    }
    free(g->orden);
    g->orden = NULL;
}

static void liberar_vecinos(Vert *vert)
{
    for (u32 j = 0 ; j < vert->grado ; j++)
    {
        vert->vecinos[j] = NULL;
    }
    free(vert->vecinos);
}

void DestruccionDelGrafo (Grafo G)
{
    for (u32 i = 0 ; i < G->nvertices ; i++){
        liberar_vecinos(G->vertices[i]);
    }
    liberar_orden(G);
    liberar_arbol(G->raiz);
    free(G->vertices);
    G->vertices = NULL;
    free(G);
}


static void vert_copy(Vert *x, u32 grado, Grafo copia, u32 idx)
{

    Vert *cvert = calloc(1, sizeof(struct Vert));
    cvert->color = x->color;
    cvert->grado = x->grado;
    cvert->index = x->index;
    cvert->nombre = x->nombre;
    cvert->vecinos = calloc(grado, sizeof(Vert *));
    copia->vertices[idx] = cvert;
}

static void copy_vecinos(Vert *copy, Vert *org, u32 grado, Grafo c, Grafo g)
{
    for (u32 i = 0 ; i < grado ; i++){
        copy->vecinos[i] = c->vertices[OrdenVecino(i, org->index, g)];
    }
}

Grafo CopiarGrafo(Grafo g)
{
    //u32 idx = 0;
    Grafo c = calloc(1, sizeof(struct GrafoSt));
    c->delta = g->delta;
    c->nlados = g->nlados;
    c->nvertices = NumeroDeVertices(g);
    c->vertices = calloc(c->nvertices, sizeof(Vert*));
    c->orden = calloc(c->nvertices, sizeof(Vert*));
    assert(c != NULL && c->vertices != NULL && c->orden != NULL);
    c->raiz = NULL;
    for (u32 i = 0 ; i < g->nvertices ; i++){
        vert_copy(g->vertices[i], Grado(i,g), c, i);
    }
    for (u32 i = 0; i < g->nvertices; i++){
        c->orden[i] = c->vertices[g->orden[i]->index];
        copy_vecinos(c->vertices[i],g->vertices[i], Grado(i,g), c, g);
    }
    return c;
}