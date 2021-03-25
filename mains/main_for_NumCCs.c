#include <stdio.h>
#include "veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    printf("%u", NumCCs(G));
    DestruccionDelGrafo(G);

    return (0);
}
