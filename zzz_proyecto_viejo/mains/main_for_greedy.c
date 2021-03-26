#include <stdio.h>
#include "../veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    for(u32 i = 0; i < NumeroDeVertices(G) ; i++)
        FijarOrden(i,G,i);

    u32 gri = Greedy(G);

    for(u32 i = 0; i < 200; i++){
        gri = Greedy(G);
        AleatorizarVertices(G,i);
    }

    printf("Gotten result  : %u\n",gri);

    DestruccionDelGrafo(G);

    return (0);
}
