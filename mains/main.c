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
    //!Primera parte
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
    
    //!Segunda parte
    printf("\n====================Datos del grafo:====================\n");

    const u32 N = NumeroDeVertices(G);
    const u32 delta = Delta(G);
    printf("Numero de vertices : %d \n",N);
    printf("Numero de lados : %d \n",NumeroDeLados(G));
    printf("Delta del grafo : %d\n",delta);

    //!3
    char bip = Bipartito(G);
    check_bipartito(bip);

    if (bip) return 0;

    //!4
    srand(f);

    //!5
    u32 gri = 0;
    u32 min = 0;
    u32 ran = 0;
    u32 min_seed = error;

    for (u32 i = 0; i < N; i++)
        FijarOrden(i,G,i);
    
    gri = Greedy(G);
    if (gri < min) 
        min = gri;
    printf("Colores: %u\n",gri);

    for (u32 i = 0; i < a; i++) {
        ran = (u32)rand();
        AleatorizarVertices(G,ran);
        gri = Greedy(G);
        if (gri < min) {
            min = gri;
            min_seed = ran;
        }
        printf("Colores: %u\n",gri);
    }

    if (min_seed != error)
        AleatorizarVertices(G,min_seed);
    else 
        for (u32 i = 0; i < N; i++)
            FijarOrden(i,G,i);

    gri = Greedy(G);

    //!6
    u32 past = 0;
    for (u32 i = 0; i < b; i++) {
        past = gri;
        OrdenPorBloqueDeColores(G,generateAndShuffle(gri,f));
        gri = Greedy(G);
        //!Sacar este print
        if (gri > past)
            print_in_red("TODO MAL, GRI > PAST");

        printf("Colores: %u\n",gri);
    }

    //!7
    u32 gri1,gri2;
    gri1 = gri2 = gri;
    Grafo g1,g2;
    u32* arr1 = NULL;
    u32* arr2 = NULL;
    u32* arr3 = NULL;
    u32 min1,min2,min3;
    min1 = min2 = min3 = error;
    min = 0;

    for (u32 i = 0; i < c; i++) {
        printf("El Mejor color: %u \n", Greedy(G));
        g1 = CopiarGrafo(G);
        g2 = CopiarGrafo(G);

        for (u32 j = 0; j < d; j++) {
            arr1 = generateAndShuffle(gri,f);
            OrdenPorBloqueDeColores(G,arr1);
            arr2 = etareneg(gri1);
            OrdenPorBloqueDeColores(g1,arr2);
            arr3 = eswap(gri2,e,f);
            OrdenPorBloqueDeColores(g2,arr3);

            gri  = Greedy(G);
            gri1 = Greedy(g1);
            gri2 = Greedy(g2);
            printf("G: %u, G1: %u, G2: %u\n",gri,gri1,gri2);

            if (gri < min1)
                min1 = gri;
            if (gri1 < min2)
                min2  = gri1;
            if (gri2 < min3)
                min3 = gri2;
        }
        
        printf("Min G: %u, Min G1: %u, Min G2: %u\n",min1,min2,min3);
        if (min1 >= min2) {
            if (min2 >= min3) {
                DestruccionDelGrafo(G);
                DestruccionDelGrafo(g1);
                G = g2;
                min = min3;
                gri = min3;
            }
            else {
                DestruccionDelGrafo(G);
                DestruccionDelGrafo(g2);
                G = g1;
                min = min2;
                gri = min2;
            }
        }
        else {
            if (min1 <= min3) {
                DestruccionDelGrafo(g2);
                DestruccionDelGrafo(g1);
                min = min1;
                gri = min1;
            }
            else {
                DestruccionDelGrafo(G);
                DestruccionDelGrafo(g1);
                G = g2;
                min = min3;
                gri = min3;
            }
        }
    }

    //!8    
    free(arr1);
    free(arr2);
    free(arr3);

    printf("Minimo color obtenido: %u\n",min);
    printf("Greedys hechos: %u\n",c*d*3);

    if (min == min3) 
        DestruccionDelGrafo(g2);
    else if (min == min2)
        DestruccionDelGrafo(g1);
    else if (min == min1)
        DestruccionDelGrafo(G);

    fclose(stdin);

    clock_t end = clock();

    double total = (double)(end-start) / CLOCKS_PER_SEC;

    printf("El programa tardo %f segundos en correr\n",total);

    return 0;
}