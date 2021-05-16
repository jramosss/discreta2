#include <stdio.h> 
#include "../RomaVictor.h"
#include "../src/utils.h"

int main (void) {
    Grafo G = ConstruccionDelGrafo();
    const u32 N = NumeroDeVertices(G);
    u32* perm = calloc(N,sizeof(u32));
    for (u32 i = 1; i <= N; i++)
        perm[i] = i;

    char res = OrdenPorBloqueDeColores(G,perm);

    printf("%d\n",res);

    return 0;
}