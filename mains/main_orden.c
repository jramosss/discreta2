#include <stdio.h> 
#include "../RomaVictor.h"
#include "../src/utils.h"

int main (void) {
    Grafo G = ConstruccionDelGrafo();
    const u32 N = NumeroDeVertices(G);
    u32* perm = calloc(N,sizeof(u32));
    u32 j = 1;
    for (u32 i = 0; i < N; i++,j++)
        perm[i] = j;

    Greedy(G);
    char res = OrdenPorBloqueDeColores(G,perm);

    printf("\n%d\n",res);

    return 0;
}