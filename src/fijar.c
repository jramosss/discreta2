#include "utils.h"
#include "../RomaVictor.h"

char FijarColor(u32 x, u32 idx, Grafo G)
{
    Vert *vert = find_vert_by_index(idx, G);

    if (vert==NULL) return 1;

    vert->color = x;
    return 0;
}

char FijarOrden(u32 i,Grafo G,u32 N){
    if (i >= G->n || N >= G->n) return 1;
    
    G->vertices[i] = G->orden_natural[N];
    G->vertices[i]->index = i;

    return 0;
}

u32 FijarPesoLadoConVecino(u32 j,u32 i,u32 p,Grafo G){
    // Ver que u32 debemos retornar, la funcion no aclara nada.
    if (i >= G->n || j >= find_vert_by_index(i,G)->grado) return error;

    Vert *vert = find_vert_by_index(i,G);
    vert->pesoslados[j] = p;

    return 0;
}

static void randomswaps(u32 *array, u32 n, u32 R){
    srand(R);
    for (u32 i = 0; i < n; i++)
        swap(&array[i],&array[((i+1) * R * rand() ) % n]);    
}

char AleatorizarVertices(Grafo G, u32 R){
    const u32 N = NumeroDeVertices(G);
    u32 *guia   = malloc(N*sizeof(u32));    // Usamos este arreglo de guia para ordenar los vertices
    if (guia == NULL) return 1;
    
    for (u32 i = 0; i < N; i++){            // Ordeno el arreglo principal de forma natural 
        FijarOrden(i, G, i);                // para olvidarme del orden con el que llego el grafo
        guia[i] = i;                        // Array que voy a ordenar de forma aleatoria
    }   

    randomswaps(guia, N, R);                // Ordena el array de forma pesudoaleatoria dependiendo de R.

    for (u32 i = 0; i < N; i++){            // De acuerdo al arreglo guia voy a reordenar el arreglo vertices de la estructura
        if (guia[i] >= N) {
            free(guia);
            return 1;
        }
        FijarOrden(i,G,guia[i]);
    }

    free(guia);

    return 0;
}