#include <time.h>
#include "../RomaVictor.h"
#include "../src/utils.h"

void test_time (Grafo G) {
    u32 R = (u32)rand();
    AleatorizarVertices(G,R);    
}

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

//TODO hacer que este programa tome parametros para saber cuantas veces correr
int main (void) {
    Grafo G = ConstruccionDelGrafo();
    //Para los tests de python usar esta linea
    //printf("%c\n",AleatorizarVertices(G,R));

    //Para ver con tus propios ojos como queda el arreglo de vertices correr esta
    //try_diff_seeds(G,3);

    //Experimental
    //try_diff_seeds_aux(G,1000);

    //Test time
    clock_t start,end;
    double total = 0;
    start = clock();
    test_time(G);
    end = clock();
    total = (double)end-start/CLOCKS_PER_SEC;
    printf("%f\n",total);

    DestruccionDelGrafo(G);

    return 0;
}
