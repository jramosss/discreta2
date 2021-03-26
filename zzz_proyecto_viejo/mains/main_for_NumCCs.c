#include <stdio.h>
#include "../veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    printf("Gotten Result: %u\n", NumCCs(G));
    DestruccionDelGrafo(G);

    return (0);
}
