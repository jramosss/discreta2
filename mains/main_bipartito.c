#include "../RomaVictor.h"
#include <time.h>

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    clock_t start = clock();

    const char resultado = Bipartito(G);

    clock_t end = clock();

    double total = (double) (end - start) / CLOCKS_PER_SEC;

    printf("Resultado: %u\n", resultado);
    printf("Tiempo : %f\n", total);
    
    DestruccionDelGrafo(G);
}