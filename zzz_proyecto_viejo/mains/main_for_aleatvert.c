#include <stdio.h>
#include "../veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();
    printf("Gotten Result: %c\n", AleatorizarVertices(G,1));
    DestruccionDelGrafo(G);

    return (0);
}