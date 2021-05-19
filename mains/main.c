#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX, INT_MIN
#include <time.h>
#include "../RomaVictor.h"
#include "../src/utils.h"

//./test 8 5 47 7 3 3 < grafos/Octo

int main(int argc,char* argv[]){
    clock_t start = clock();
    char* p;
    errno = 0;
    u32 a,b,c,d,e,f;
    a = b = c = d = e = f = 0;

    if (argc != 7) {
        printf("Cantidad invalida de argumentos: %d\n",argc);
        exit(1);
    }
    else {
        a = (u32)strtol(argv[0], &p, 10);;
        b = (u32)strtol(argv[1], &p, 10);;
        c = (u32)strtol(argv[2], &p, 10);;
        d = (u32)strtol(argv[3], &p, 10);;
        e = (u32)strtol(argv[4], &p, 10);;
        f = (u32)strtol(argv[5], &p, 10);;
    }

    printf("ARGS: %u %u %u %u %u %u\n",a,b,c,d,e,f);

    //Ver como hacer para cargar el grafo a mano
    //? se hara solo debido al construccion del grafo?

    Grafo G = ConstruccionDelGrafo();
    
    printf("\n====================Datos del grafo:====================\n");

    const u32 N = NumeroDeVertices(G);
    const u32 delta = Delta(G);
    printf("Numero de vertices : %d \n",N);
    printf("Numero de lados : %d \n",NumeroDeLados(G));
    printf("Delta del grafo : %d\n",delta);

    char bip = Bipartito(G);
    check_bipartito(bip);

    if (bip) exit(0);

    for (u32 i = 0; i < N; i++)
        FijarOrden(i,G,i);
    
    srand(f);
    char alv;
    u32 gri = 0;
    u32 max = 0;
    u32 ran = 0;
    u32 max_seed = 0;

    for (u32 i = 0; i < a; i++) {
        ran = (u32)rand();
        alv = AleatorizarVertices(G,ran);
        if (!alv)
            print_in_red("Se rompio el alv");
        gri = Greedy(G);
        if (gri > max) {
            max = gri;
            max_seed = ran;
        }
        printf("Colores: %u\n",gri);
    }

    AleatorizarVertices(G,max_seed);
    gri = Greedy(G);
    u32 past = 0;

    for (u32 i = 0; i < b; i++) {
        past = gri;
        gri = Greedy(G);
        OrdenPorBloqueDeColores(G,generateAndShuffle(gri));
        if (gri < past)
            print_in_red("TODO MAL, GRI < PAST");

        printf("Colores: %u\n",gri);
    }

    u32 gri1,gri2;
    gri1 = gri2 = 0;
    Grafo g1,g2;
    u32* arr1;
    u32* arr2;
    u32* arr3;
    arr1 = arr2 = arr3 = NULL;
    u32 min1,min2,min3;
    min1 = min2 = min3 = error;

    for (u32 i = 0; i < c; i++) {
        g1 = CopiarGrafo(G);
        g2 = CopiarGrafo(G);
        for (u32 j = 0; j < d; j++) {
            gri = Greedy(G);
            gri1 = Greedy(g1);
            gri2 = Greedy(g2);
            printf("G: %u, G1: %u, G2: %u\n",gri,gri1,gri2);
            arr1 = generateAndShuffle(gri);
            OrdenPorBloqueDeColores(G,arr1);
            arr2 = generate(gri1);
            OrdenPorBloqueDeColores(g1,arr2);
            arr3 = etareneg(gri2,e);
            OrdenPorBloqueDeColores(g2,arr3);

            if (gri < min1)
                min1 = gri1;
            if (gri1 < min2)
                min2  = gri1;
            if (gri2 < min3)
                min3 = gri2;
        }
        printf("Min G: %u, Min G1: %u, Min G2: %u\n",min1,min2,min3);
        DestruccionDelGrafo(g1);
        DestruccionDelGrafo(g2);
    }

    free(arr1);
    free(arr2);
    free(arr3);

    printf("Greedys hechos: %u\n",c*d*3);

    DestruccionDelGrafo(G);

    fclose(stdin);

    clock_t end = clock();

    double total = (double)(end-start) / CLOCKS_PER_SEC;

    printf("El programa tardo %f segundos en correr\n",total);

    return 0;
}