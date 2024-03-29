#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "../src/utils.h"
#include "../RomaVictor.h"

const double MAX_TIME = 60*15;


static bool coloreo_propio (Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); i++)
        for(u32 j = 0; j < Grado(i,G) ; j++)
            if(Color(i,G) == ColorVecino(j,i,G))
                return false;
    return true;
}

int main(void) {
    Grafo G = ConstruccionDelGrafo();

    clock_t start = clock();

    const char resultado = Bipartito(G);

    clock_t end = clock();

    double total = (double) (end - start) / CLOCKS_PER_SEC;

    if (!coloreo_propio(G))
        print_in_red("EL COLOREO NO ES PROPRIO");

    printf("%u %f", (u32)resultado,total);
    
    DestruccionDelGrafo(G);
}