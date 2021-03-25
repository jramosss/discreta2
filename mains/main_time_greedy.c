#include <stdio.h>
#include <time.h>
#include "veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();
    for(u32 i = 0; i < NumeroDeVertices(G) ; i++){
        FijarOrden(i,G,i);
    }
    clock_t start,end;
    double total = 0;
    start = clock();
    u32 gri = Greedy(G);
    u32 niteraciones = 99;
    for(u32 i = 0; i < niteraciones; i++){
        gri = Greedy(G);
        AleatorizarVertices(G,i);
    }
    end = clock();
    total = (double)(end-start)/CLOCKS_PER_SEC;
    printf("%d GREEDYS TARDARON %f SEGUNDOS\n",niteraciones,total);
    DestruccionDelGrafo(G);

    return (0);
}
