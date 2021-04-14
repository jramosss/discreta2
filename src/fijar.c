#include <string.h>
#include <time.h>
#include "utils.h"
#include "../RomaVictor.h"

char FijarColor(u32 x, u32 idx, Grafo G)
{
    Vert *vert = find_vert_by_index(idx, G);

    if (vert==NULL) return '1';

    vert->color = x;
    return '0';
}

char FijarOrden(u32 i,Grafo G,u32 N){
    if (i >= G->n || N >= G->n) return '1';
    
    G->vertices[i] = G->orden_natural[N];
    G->vertices[i]->index = i;

    return '0';
}

u32 FijarPesoLadoConVecino(u32 j,u32 i,u32 p,Grafo G){
    // Ver que u32 debemos retornar, la funcion no aclara nada.
    if (i >= G->n || j >= find_vert_by_index(i,G)->grado) return error;

    Vert *vert = find_vert_by_index(i,G);
    vert->pesoslados[j] = p;
    return 0;
}


char AleatorizarVertices(Grafo G,u32 R) {
    srand(R);
    const u32 N = NumeroDeVertices(G);
    const u32 random = (u32)rand();
    char* used = malloc(N*sizeof(u32));
    if (used == NULL) return '1';
    u32 new_pos, i, n;
    new_pos = i = n = 0;

    //Ordenamos el arreglo segun el orden natural
    for (u32 j = 0; j < N; j++)
        FijarOrden(j,G,j);

    memset(used,(u32)error,N);

    while (i < N-1) {
        new_pos = (i*R*random+n)%N;  
        if (used[new_pos] == (char)error) {
            used[new_pos] = '1';
            if (FijarOrden(i,G,new_pos) == '1') return '1';
            i++;
        }
        else
            n++;
    }

    for (u32 t = 0; t < N; t++) {
        if (used[t] == (char)error) {
            FijarOrden(N-1,G,t);
            break;
        }
    }

    free(used);

    return '0';
}

