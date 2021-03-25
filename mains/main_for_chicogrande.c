#include <stdio.h>
#include "veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    printf("%c", ChicoGrandeBC(G));
    DestruccionDelGrafo(G);

    return (0);
}