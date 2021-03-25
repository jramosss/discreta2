#include <stdio.h>
#include "../veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    printf("Gotten Result: %d\n", ChicoGrandeBC(G));
    DestruccionDelGrafo(G);

    return (0);
}