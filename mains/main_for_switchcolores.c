#include <stdio.h>
#include "veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    printf("%c", SwitchColores(G,0,1));
    DestruccionDelGrafo(G);

    return (0);
}