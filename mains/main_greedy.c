#include "../RomaVictor.h"
#include <time.h>

int main(void) {
    clock_t start, end;
    double total;

    Grafo G = ConstruccionDelGrafo();
    for (u32 i = 0; i < NumeroDeVertices(G); i++) 
        FijarOrden(i,G,i);  

    start = clock();
    u32 colores = Greedy(G);
    end = clock();
    total = (double) (end - start) / CLOCKS_PER_SEC;
    printf("COLORES: %u\n", colores);
    printf("TIEMPO: %f\n", total);
    DestruccionDelGrafo(G);
}