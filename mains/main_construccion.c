#include <stdio.h>
#include <time.h>
#include "../RomaVictor.h"

int main(void) {
    clock_t start = clock();

    Grafo g = ConstruccionDelGrafo();

    clock_t end = clock();

    double total = (double)((end-start)/CLOCKS_PER_SEC);

    printf("Construccion: %f\n",total);

    if (g == NULL) return 0;

    start = clock();
    DestruccionDelGrafo(g);
    end   = clock();
    total = (double)((end-start)/CLOCKS_PER_SEC);

    printf("Destruccion: %f\n",total);

    return 0;
}