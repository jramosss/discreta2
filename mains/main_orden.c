#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include "../RomaVictor.h"
#include "../src/utils.h"

void print (Grafo G) {
    printf("Colores: [");
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
        printf(i == NumeroDeVertices(G)-1 ? "%u" : "%u,",Color(i,G));
    printf("]");

    printf("\nVertices\n");
    print_arr_vertices(G);

    printf("\nColores de greedy: %u\n",Greedy(G));
}

int main (int argc,char** argv) {
    long times = 1;
    char* p;
    errno = 0;
    if (argc == 2) {
        times = strtol(argv[1], &p, 10);
        if (errno != 0 || *p != '\0' || times > INT_MAX || times < INT_MIN) {
            printf("Error en la conversion a entero\n");
            return 1;
        }
    }

    Grafo G = ConstruccionDelGrafo();

    u32 colores = Greedy(G);

    u32* perm = calloc(colores,sizeof(u32));

    perm = generate(colores);
    //perm = etareneg(colores);

    //u32 j = 0;
    //for (u32 i = 15; i < colores+15; i++,j++)
    //    perm[j] = i;

    clock_t start = clock();

    for (u32 i = 0 ; i < times; i++)
        OrdenPorBloqueDeColores(G,perm);

    clock_t end = clock();

    double total = (double)(end-start)/CLOCKS_PER_SEC;
    
    printf("%f\n",total);

    print(G);

    DestruccionDelGrafo(G);
    free(perm);

    return 0;
}