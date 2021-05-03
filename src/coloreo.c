#include <assert.h>
#include "cola.h"
#include <string.h>
#include "../RomaVictor.h"
#include "utils.h"

/* 
    Cotas para greedy
    X(G) <= Delta + 1.
    Si G es conexo, entonces X(G) <= Delta, a menos que G sea un ciclo impar o un grafo completo.
*/  
u32 Greedy(Grafo G) {
    u32 colorsQty       =   0;
    u32 gradoVertice    =   0;
    u32 color           =   error;
    const u32 maxColors =   Delta(G) + 1;
    const u32 N         =   NumeroDeVertices(G);
    char *usedColors    =   malloc(maxColors*sizeof(char));
    if (usedColors == NULL) return error;
    char *visitados      =   calloc(N, sizeof(u32));
    if(visitados == NULL) {
        free(usedColors);
        return error;
    }
    
    // Pinto al primer vertice con 0 e incremento la cantidad de colores.
    FijarColor(0, 0, G);
    visitados[0] =  1;
    colorsQty++;

    //Luego por cada vertice, siempre intento pintar con el menor color posible.
    for (u32 vert = 1; vert < N; vert++) {
        gradoVertice = Grado(vert,G);
        // Reset a los colores usados por los vecinos.
        memset(usedColors, 0, gradoVertice);

        for (u32 vec = 0; vec < gradoVertice; vec++)
            //para cada vecino visitado seteo su color como usado.
            if (visitados[OrdenVecino(vec, vert, G)])
                usedColors[ColorVecino(vec, vert, G)] = 1;

        /*  Luego busco segun la cantidad de colores que utilice hasta el
            momento en usedColors resultante, El menor color posible para
            colorear el vertice.
        */
        
        for (u32 k = 0; k < maxColors; k++) {
            if (!usedColors[k]) {
                color = k;
                break;
            }
        }
        if (color == error) return error;

        /*  Checkeo si tengo que utilizar un nuevo color. 
            De ser asi aumento colorsQty 
        */
        if (color == colorsQty) colorsQty++;
        /*  Una vez encontrado el minimo color para el vertice i, lo pinto y lo
            guardo en visitados.
        */
    
        FijarColor(color, vert, G);
        visitados[vert] = 1;
    }

    free(visitados);
    free(usedColors);

    return colorsQty;
}


/* Devuelve 1 si el grafo es bipartito, 0 en caso contrario.
    Si devuelve 1 queda coloreado con 2 colores, y si 
    devuelve 0 queda coloreado con un coloreo propio. */
char Bipartito(Grafo G){
    u32 nvertices = NumeroDeVertices(G);
    u32 *visitados = calloc(nvertices, sizeof(u32));      // Arreglo que indica los vertices visitados (1) 
    if (visitados == NULL) return 7;
    queue_t *queue = createQueue();
    if (queue == NULL) {
        free(visitados);
        return 7;
    }
    u32 v;

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
                            return 0;
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
    return 1;
}