#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

/* --------- Initialize the structs --------- */

/* Initialize a vert */
Vert *vert_create (u32 name, u32 mlados)
{
    Vert *newvert = calloc(1, sizeof(struct Vert));
    newvert->vecinos = calloc(mlados, sizeof(Vert*));
    newvert->nombre = name;
    newvert->index = name;
    newvert->visited = 0;       //TODO usemos booleanos
    newvert->grado = 0;
    newvert->color = 4294967295;
    newvert->vert_iz = NULL;
    newvert->vert_de = NULL;
    return newvert;
}


/* --------- Extract info from file --------- */

/* Parse the number of verts from file */
static u32 number_of_vertices (FILE *fp)
{
    char stn[MAXCHAR];
    char stm[MAXCHAR];
    u32 n = 0;

    fscanf(fp, "%1s %s", stn, stm);
    while ((!feof(fp)) && (n == 0))
    {
        strcat(stn," ");
        strcat(stn,stm);
        if (memcmp(stn,"p edge",7)==0)
        {
            fscanf(fp, "%s", stn);
            n = (u32)atoi(stn);
        }
        fscanf(fp, "%1s %s", stn, stm);
    }
    fseek(stdin,0,SEEK_SET);
    return n;
}

/* Parse the number of edges, from the file adress (filename) */
static u32 number_of_edges (FILE *fp)
{
    char stn[MAXCHAR];
    char stm[MAXCHAR];
    u32 n = 0;

    fscanf(fp, "%1s %s", stn, stm);
    while ((!feof(fp)) && (n == 0))
    {
        strcat(stn," ");
        strcat(stn,stm);
        if (memcmp(stn,"p edge",7)==0)
        {
            fscanf(fp, "%s %s", stn, stm);
            n = (u32)atoi(stm);  
        }
        fscanf(fp, "%1s %s", stn, stm);
    }
    fseek(stdin,0,SEEK_SET);
    return n;
}

/* Return a array with tuples of edges */
Tuple *array_of_tuples (FILE *filename, Grafo graph)
{
    char stn[MAXCHAR];
    char stx[MAXCHAR];
    char sty[MAXCHAR];
    char stp[MAXCHAR];
    char ult[MAXCHAR];
    graph->nlados = number_of_edges(stdin);
    graph->nvertices = number_of_vertices(stdin);
    Tuple *array = calloc(graph->nlados, sizeof(Tuple));
    Tuple xy;
    u32 x = 0;
    u32 y = 0;

    sprintf(ult, "%d", graph->nlados);

    fscanf(filename, "%s %s %s %s", stp, stx, sty, stn); //Solo en caso que no haya comentarios
    while (!feof(filename))
    {
        if (memcmp(stn,ult,strlen(ult))==0)
        {
            for (u32 i = 0; i < graph->nlados; i++)
            {
                fscanf(filename, "%s %s %s", stn, stx, sty);
                x = (u32)atoi(stx);
                y = (u32)atoi(sty);
                xy.vx = x;
                xy.vy = y;
                array[i] = xy;
            }
        }
        fscanf(filename, "%s",stn);
    }
    return array;
}


/* --------- Aux functions --------- */

/* Aux of tree_contains*/
static bool tree_contains_aux (Vert* aux, u32 name) {
    if (aux != NULL){
        if (aux->nombre == name)
            return true;        
        else if (tree_contains_aux(aux->vert_de,name) || tree_contains_aux(aux->vert_iz,name))
             return true;
    }
    return false;
}

/* check if a vert its contain in the tree */
static bool tree_contains (u32 name, Grafo G) {
    return tree_contains_aux(G->raiz,name); //Tengo que llamar a una funcion auxiliar, ya que necesito que
                                            // G->raiz, sino, al hacer recursion se me hace lio.
}

/* search a vert in tree by his name*/
Vert *find_vert_by_name(u32 name, Vert *raiz){
    Vert *aux = NULL;
    if (raiz != NULL){
        if (raiz->nombre == name){
            return raiz;
        }

        else if (name > raiz->nombre) {
            if (raiz->vert_de != NULL)
                aux = find_vert_by_name(name, raiz->vert_de);
        }

        else if (name < raiz->nombre) {
            if (raiz->vert_iz != NULL)
                aux = find_vert_by_name(name, raiz->vert_iz);
        }
    }
    return aux;
}

/* add a vert in a tree by numeric order */
static void addvert_graph(Vert *vert, GrafoSt *graph, Vert *raiz)
{
    if ( graph->raiz == NULL){
        graph->raiz = vert;

    } else if (vert->nombre < raiz->nombre){
        if (raiz->vert_iz != NULL){
            addvert_graph(vert, graph,raiz->vert_iz);
        } else {
            raiz->vert_iz = vert;
        }

    } else if (vert->nombre > raiz->nombre){
        if (raiz->vert_de != NULL){
            addvert_graph(vert, graph, raiz->vert_de);
        } else {
            raiz->vert_de = vert;
        }
    }    
}

/* ------- Fill the orden graph ---------- */ // Esta funcion es llamada en graph_fill, a medida que creo un vertice, agrego su puntero en el arreglo.
void vertices_fill(Grafo graph, u32 i, Vert *a)
{
    graph->vertices[i] = a;
    graph->vertices[i]->index = i;       //Con esto el indice que el vertice tiene en el arbol corresponderia al index de su orden en el arreglo.
}


/* --------- fill the graph struct --------- */

/* fill the tree of the given graph */
void graph_fill(Grafo g)
{
    Vert *vertx;
    Vert *verty;
    u32 j = 0;                              // Esta variable corresponde a la posicion en el arreglo *orden del struct Grafo.

    for (u32 i = 0; i < g->nlados; i++)
    {
        if (!tree_contains(g->parseo[i].vx,g) || !tree_contains(g->parseo[i].vy,g)) {
            
            if ((!tree_contains(g->parseo[i].vx,g) && !tree_contains(g->parseo[i].vy,g)) ) { // vx no esta en el arbol
    
                vertx = vert_create(g->parseo[i].vx,g->nlados);
                addvert_graph(vertx, g, g->raiz);
                vertices_fill(g, j, vertx);
                j++;


                verty = vert_create(g->parseo[i].vy,g->nlados);
                addvert_graph(verty, g, g->raiz);
                vertices_fill(g, j, verty);
                j++;
                
            } else if ((tree_contains(g->parseo[i].vx,g) == true) && (tree_contains(g->parseo[i].vy,g) == false)){
                verty = vert_create(g->parseo[i].vy,g->nlados);
                addvert_graph(verty, g, g->raiz);
                vertices_fill(g, j, verty);
                j++;
            }
             else if ((tree_contains(g->parseo[i].vx,g) == false) && (tree_contains(g->parseo[i].vy,g) == true)){
                vertx = vert_create(g->parseo[i].vx,g->nlados);
                addvert_graph(vertx, g, g->raiz);
                vertices_fill(g, j, vertx);
                j++;
            }
        }
    }
}

/* fill the vecinos of the graph */
void fill_vecinos(Grafo graph)
{
    u32 vertx;
    u32 verty;
    Vert *x;
    Vert *y;
    for (u32 i = 0; i < graph->nlados; i++){
        vertx = graph->parseo[i].vx;
        verty = graph->parseo[i].vy;

        x = find_vert_by_name(vertx, graph->raiz);
        y = find_vert_by_name(verty, graph->raiz);
        x->vecinos[x->grado] = y;
        y->vecinos[y->grado] = x;
        x->grado++;
        y->grado++;
    }
}
