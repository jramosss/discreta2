#include "../RomaVictor.h"
#include "../src/utils.h"

void try_diff_seeds (Grafo G,u32 times) {
    u32 R = 0;
    for (u32 i = 0; i < times; i++) {
        AleatorizarVertices(G,R);
        printf("Con R = %u\n",R);
        R++;
        print_arr_vertices(G);
    }
}

void just_results (Grafo G,u32 R){
    printf("%c\n",AleatorizarVertices(G,R));
}

int main (void) {
    Grafo G = ConstruccionDelGrafo();
    const u32 R = 3;

    //Para los tests de python usar esta funcion
    just_results(G,R);

    //Para ver con tus propios ojos como queda el arreglo de vertices correr esta
    //try_diff_seeds(G,3);

    return 0;
}