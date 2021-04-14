#include "../RomaVictor.h"
#include "../src/utils.h"

void try_diff_seeds_aux (Grafo G,u32 times) {
    u32 R = 1;
    for (u32 i = 0; i < times; i++) {
        AleatorizarVertices(G,R);
        print_arr_vertices(G);
        printf("[");
        for (u32 j = 0; j < NumeroDeVertices(G); j++)
            printf(j == NumeroDeVertices(G)-1 ? "%u" : "%u,",G->orden_natural[j]->nombre);
        printf("]");
        R++;
    }
}

void try_diff_seeds (Grafo G,u32 times) {
    u32 R = 1;
    for (u32 i = 0; i < times; i++) {
        AleatorizarVertices(G,R);
        printf("Con R = %u: \n",R);
        R++;
        print_arr_vertices(G);
    }
}

int main (void) {
    Grafo G = ConstruccionDelGrafo();
    const u32 R = 5;
    //Para los tests de python usar esta linea
    //printf("%c\n",AleatorizarVertices(G,R));

    //Para ver con tus propios ojos como queda el arreglo de vertices correr esta
    //try_diff_seeds(G,3);

    //Experimental
    try_diff_seeds_aux(G,40);

    return 0;
}