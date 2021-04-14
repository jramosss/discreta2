#include "../RomaVictor.h"
#include "cola.h"

/* Devuelve 1 si el grafo es bipartito, 0 en caso contrario.
    Si devuelve 1 queda coloreado con 2 colores, y si 
    devuelve 0 queda coloreado con un coloreo propio. */
char Bipartito(Grafo G){
    const u32 nvertices = NumeroDeVertices(G);
    char *visitados = calloc(nvertices, sizeof(char));      // Arreglo que indica los vertices visitados (1) 
    queue_t *queue = createQueue();
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
                            // Greedy(G);
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

