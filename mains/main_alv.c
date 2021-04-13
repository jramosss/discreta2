#include "../RomaVictor.h"
#include "../src/utils.h"

void try_diff_seeds_aux (Grafo G,u32 times) {
    u32 R = 1;
    for (u32 i = 0; i < times; i++) {
        AleatorizarVertices(G,R);
        printf("Con R = %u: \n",R);
        if (i % 2 == 0) R++;
        print_arr_vertices(G);
        blank(2);
    }
}

void try_diff_seeds (Grafo G,u32 times) {
    u32 R = 0;
    for (u32 i = 0; i < times; i++) {
        AleatorizarVertices(G,R);
        printf("Con R = %u: \n",R);
        R++;
        print_arr_vertices(G);
    }
}

int main (void) {
    Grafo G = ConstruccionDelGrafo();
    const u32 R = 3;

    //Para los tests de python usar esta linea
    printf("%c\n",AleatorizarVertices(G,R));

    //Para ver con tus propios ojos como queda el arreglo de vertices correr esta
    //try_diff_seeds(G,R);

    //Experimental
    //try_diff_seeds_aux(G,6);

    return 0;
}