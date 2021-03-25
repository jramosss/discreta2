#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cola.h"
#include "../veinteveinte.h"

//! Esto esta para atras, no podemos tener una complejidad de O(2n²)
u32 Greedy(Grafo G){

    const u32 error = 4294967295;
    const u32 nverts = NumeroDeVertices(G);
    const u32 tam = Delta(G) + 1;
    char *visitados = calloc(nverts,sizeof(char));  // Arreglo que indica los vertices visitados
    char *usados = calloc(tam,sizeof(char));        // Arreglo que indica los colores usados.

    if (visitados == NULL || usados == NULL) 
        return error;

    FijarColor(0,0,G);                              // Comenzamos pintando el 1er vertice con el color 0
    visitados[0] = 1;
    u32 cantcol = 1;
    for (u32 i = 1; i < NumeroDeVertices(G); i++){  // Itera vertices
        for (u32 j = 0; j < Grado(i,G); j++)
            if (visitados[OrdenVecino(j,i,G)]) 
                usados[ColorVecino(j,i,G)] = 1;

        for (u32 p = 0; p < tam; p++) {            // Vemos con que color minimo puedo pintar el i-vertice para mantener un coloreo propio
            if (!usados[p]) {
                FijarColor(p, i, G);
                visitados[i] = 1;
                memset(usados,0,tam);               // Reseteamos el arreglo usados con 0's, porque no queremos tener marcado los colores 
                                                    // de los vecinos del vertice anterior
                if(p == cantcol)
                    cantcol++;                      // Solo aumento cantcol cuando el color con el que decido pintar iguala a la cantidad de
                                                   // de colores usados hasta el momento.
                break;
            }
        }

    }
    free(visitados);
    free(usados);
    usados = NULL;
    visitados = NULL;

    return cantcol;
}


/* twice born */
/* Devuelve 1 si el grafo es bipartito, 0 en caso contrario.
    Si devuelve 1 queda coloreado con 2 colores, y si 
    devuelve 0 queda coloreado con un coloreo propio. */
char Bipartito(Grafo G){
    const u32 nvertices = NumeroDeVertices(G);
    char *visitados = calloc(nvertices, sizeof(char));      // Arreglo que indica los vertices visitados (1) 
    queue_t *queue = createQueue();
    u32 v;

    assert(visitados != NULL && queue != NULL);             // En caso de que el calloc falle

    for (u32 i = 0; i < nvertices; i++){                    // Iteramos en los vertices, y por cada vertice (v) no visitado
                                                            // visitamos sus vecinos verificando que si ya estan pintados
        if (visitados[i] == 0) {                            // se mantenga el coloreo propio, de lo contrario lo agregamos
            enqueue(i,queue);                               // a la cola y lo pintamos con !Color(v,G)
            visitados[i] = 1;
            FijarColor(0, i, G);

            while (!isEmpty(queue)) {
            
                v = dequeue(queue);
                            
                for (u32 j = 0; j < Grado(v,G); j++) {
            
                    if (visitados[OrdenVecino(j,v,G)]){
                        if (ColorVecino(j,v,G) == Color(v,G)){
                            free(visitados);
                            removeQueue(queue);
                            Greedy(G);
                            return '0';
                        }
                    }else {
                        enqueue(OrdenVecino(j,v,G),queue);
                        visitados[OrdenVecino(j,v,G)] = 1;
                        FijarColor(1-Color(v,G),OrdenVecino(j,v,G),G);
                    }
                }
            }
        }
    }

    free(visitados);
    removeQueue(queue);
    return '1';
}

/* Funcion auxiliar de qsort 
*  Ordenacion decreciente */
static int cmp_dec(const void *a, const void *b)
{
    u32 bs = *(u32 *)b;
    u32 as = *(u32 *)a;
    return (int)(bs - as);
}

/* Si i,j estan dentro del rango aceptado, entonces intercambia los colores i j */
char SwitchColores(Grafo G, u32 i, u32 j){
    u32 nvertices = NumeroDeVertices(G);
    u32 *colors = calloc(nvertices, sizeof(u32));       // Arreglo de colores
    assert(colors != NULL);  
    u32 cant = 0;
    u32 color = 0;

    for (u32 k = 0; k < nvertices; k++){                // Llenado del arreglo colors con el color del k-vertice
        colors[k] = Color(k, G);
    }
    
    qsort(colors, nvertices, sizeof(u32), cmp_dec);     // Ordenamos para tener en la posicion 0 el mayor color utilizado
    cant = colors[0] + 1;                               // Calculamos la cantidad de colores utilizados
    
    if (i < cant && j < cant){
        
        for (u32 k = 0; k < nvertices; k++){            // Itera vertices y busco los vertices de color i para fijarles el color j
            color = Color(k, G);                        // y viceversa
            if (color == i){
                FijarColor(j, k, G);
            } else if (color == j){
                FijarColor(i, k, G);
            }
        }
        free(colors);
        colors = NULL;
        return '0'; 
    
    } else {
        free(colors);
        colors = NULL;
        return '1';
    }

}