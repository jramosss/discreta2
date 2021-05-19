#include <stdlib.h>
#include <stdbool.h>
#include "../RomaVictor.h"


int main (void) {
  Grafo G = ConstruccionDelGrafo();
  bool repited = false;

  Greedy(G);

  for (u32  i = 0; i < NumeroDeVertices(G); i++) {
    for (u32 j = 0; j < Grado(i, G); j++) {
        if (Color(i, G) == ColorVecino(j,i,G)) {
          printf("se repitio %u con su vecino %u \n", i,j);
          repited = true;
        }
    }
  }

  if (repited) {
    printf("El coloreo no es propio \n");
  }

  return 0;
}