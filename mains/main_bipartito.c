#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "../src/utils.h"
#include "../RomaVictor.h"

const double MAX_TIME = 60*15;

static bool ordena_bien (Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G)-1; i++)
        if(Grado(i,G) < Grado(i+1,G))
            return false;
    return true;
}

static bool coloreo_propio (Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); i++)
        for(u32 j = 0; j < Grado(i,G) ; j++)
            if(Color(i,G) == ColorVecino(j,i,G))
                return false;
    return true;
}

int main (void){

    clock_t start_t, end_t; 
    double total_t;

    u32 bipartito = 0;
    Grafo G = ConstruccionDelGrafo();

    if(G == NULL) 
        printf("\nFallo la construccion del grafo\n");
    else {
        start_t = clock();
        blank(1);

        printf("\n====================BIPARTITO====================\n");
            // 1 es true
            char bip = Bipartito(G);
            check_cond(bip=='1',"El grafo es bipartito","El grafo no es bipartito");
            end_t = clock();
            total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
            if(bip=='1') {
                printf("\nLa funcion bipartito tardo %f segundos en ejecutarse\n\n",total_t);
            } else {
                printf("\nLa funcion bipartito + greedy tardo %f segundos en ejecutarse\n\n",total_t);
            }
            check_cond(coloreo_propio(G), "El coloreo es propio", "El coloreo no es propio");

        DestruccionDelGrafo(G);

    }


}