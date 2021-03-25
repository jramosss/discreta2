#include <stdio.h>
#include "veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();
    for(u32 i = 0; i < NumeroDeVertices(G) ; i++){
        FijarOrden(i,G,i);
    }
    u32 gri = Greedy(G);
    for(u32 i = 0; i < 200; i++){
        gri = Greedy(G);
        AleatorizarVertices(G,i);
    }
    //gri = Greedy(G); Despues pruebo con mas iteraciones de greedy, a ver si lo que influye es el orden o las iteraciones
    //gri = Greedy(G);
    printf("%u", gri);
    DestruccionDelGrafo(G);

    return (0);
}
