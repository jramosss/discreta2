#include <stdio.h>
#include <time.h>
#include "parser.h"

static char es_coloreo_propio(Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        for(u32 j = 0; j < Grado(i,G); j++){
            if(ColorVecino(j,i,G) == Color(i,G)){
                return 0;
            }
        }
    }
    return 1;
}

int main (void){
    clock_t start_c,end_c;
    double total = 0;
    start_c = clock();
    
    Grafo G = ConstruccionDelGrafo();

    end_c = clock();
    total = (double)(end_c - start_c) / CLOCKS_PER_SEC;
    printf("Construccion tardo %f segundos\n",total);
    total = 0;

    u32 gri = Greedy(G);
    printf("Greedy sin orden %u\n",gri);
    for(u32 i = 0; i < NumeroDeVertices(G) ; i++){
        FijarOrden(i,G,i);
    }

    clock_t start,end;
    start = clock();
    
    for(u32 i = 0; i < 1000 ; i++){
        gri = Greedy(G);
        printf(es_coloreo_propio(G) ? "Es coloreo propio\n" : "El coloreo no es propio\n");
        AleatorizarVertices(G,i);
    }
    //gri = Greedy(G); Despues pruebo con mas iteraciones de greedy, a ver si lo que influye es el orden o las iteraciones
    //gri = Greedy(G);
    printf("Despues de 1000 iteraciones, greedy coloreo con %u colores", gri);
    DestruccionDelGrafo(G);

    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n PROGRAMA TOTAL tardo %f segundos en ejecutarse\n",total);

    return (0);
}