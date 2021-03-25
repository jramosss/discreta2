#include <stdio.h>
#include "veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    if(WelshPowell(G) == '1'){
      printf("Algo anduvo mal en Welsh Powell\n");
    }

    printf("%u", Greedy(G));
    DestruccionDelGrafo(G);

    return (0);
}
