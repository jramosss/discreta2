#include <stdio.h>
#include "../RomaVictor.h"
#include "../src/utils.h"

int main (void) {
    Grafo G = ConstruccionDelGrafo();

    /*
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
        perm[i] = (u32)rand() % NumeroDeVertices(G);
    */

    u32 colores = Greedy(G);

    printf("Colores de greedy: %u\n",colores);

    u32* perm = calloc(colores,sizeof(u32));

    for (u32 i = 0; i < colores; i++)
        perm[i] = i;

    printf("\nObc: %c\n",OrdenPorBloqueDeColores(G,perm));

    printf("Colores: [");
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        printf(i == NumeroDeVertices(G)-1 ? "%u" : "%u,",Color(i,G));
    }
    printf("]");

    printf("Vertices\n");
    print_arr_vertices(G);

    colores = Greedy(G);

    printf("\nColores de greedy: %u\n",colores);

    return 0;
}