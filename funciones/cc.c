#include <assert.h>
#include "../veinteveinte.h"

static char BFS(Grafo G, u32 raiz, u32 size, u32 *recorridos){
    u32 *visitados = calloc(size, sizeof(u32));
    u32 *cola = calloc(size, sizeof(u32));
    assert(visitados != NULL);
    assert(cola != NULL);
    u32 v = 0;
    u32 q_size = 0;
    u32 primero = 0;                        // Seteo los elementos de la pseudo-cola
    u32 hueco = 0; 
    u32 vecino = 0;
    u32 grado = 0;
    visitados[raiz] = 1;                    // marco la raiz como visitada
    recorridos[raiz] = 1;
    cola[0] = raiz;
    q_size++;
    hueco = 1;
    while (q_size){
        v = cola[primero];                  // comienzo por el primer elemento
        grado = Grado(v, G);
        for (u32 i = 0; i < grado; i++){
            vecino = OrdenVecino(i,v,G);
            if (visitados[vecino] == 0){    //visito cada vecino de v , si no fue visitado lo agg a la cola,
                visitados[vecino] = 1;
                recorridos[vecino] = 1;
                cola[hueco] = vecino;
                q_size++;
                hueco++;
                if (hueco == size){
                    hueco = 0;
                } 
            }
        }
        primero++;
        if ((primero) == size){
            primero = 0;
        }
        q_size--;
    }
    
    for (u32 i = 0; i < size; i++){         // Verificamos si llegamos a todos los vertices, de lo contrario retornamos '0'
        if (visitados[i] == 0){
            free(visitados);
            free(cola);
            visitados = NULL;
            cola = NULL;
            return 0;
        }
    }
    free(visitados);
    free(cola);
    visitados = NULL;
    cola = NULL;
    return 1;
}

u32 NumCCs(Grafo G){
    char cc = 0;                            // Flag que representa si se pudo llegar o no a todos los vertices
    u32 n = 0;                              // Cantidad de componentes conexas
    u32 nvertices = NumeroDeVertices(G);
    u32 *recorridos = calloc(nvertices, sizeof(u32));
    assert(recorridos != NULL);
    for (u32 vertice = 0; vertice < nvertices; vertice++){      // Recorremos los vertices no visitados
        if (recorridos[vertice] == 0){                          // y verificamos que de ahi se pueda llegar a los restantes
            cc = BFS(G, vertice, nvertices, recorridos);
            if(cc){                                             
                free(recorridos);
                return 1;
            } else {                                            // Si no pude llegar a todos los vertices sumo una nueva cc
                n++;
            }
        }
    }

    free(recorridos);
    return n;
}