#include <stdio.h>
#include "../veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    if(WelshPowell(G) == '1'){
      printf("Algo anduvo mal en Welsh Powell\n");
    }

    printf("Gotten Result: %u\n", Greedy(G));
    DestruccionDelGrafo(G);

    return (0);
}
