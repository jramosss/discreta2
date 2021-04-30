#include <stdio.h>
#include <time.h>
#include "../RomaVictor.h"

static void display_naturalOrder (Grafo G){
    printf("\nVertices orden natural: [");
    for(u32 i = 0; i < (G->n)-1; i++)
        printf("%d,",G->orden_natural[i+1]->nombre);
    printf("]\n");
}

static void display_normalOrder (Grafo G){
    printf("\nVertices orden normal: [");
    for(u32 i = 0; i < G->n; i++)
        printf("%d,",G->vertices[i]->nombre);
    printf("]\n");
}


int main(void) {
    clock_t start = clock();

    Grafo g = ConstruccionDelGrafo();

    clock_t end = clock();

    double total = (double)((end-start)/CLOCKS_PER_SEC);

    printf("Construccion: %f\n",total);

    if (g == NULL) return 0;
    
    //Comenten estas dos lineas si quieren usar los tests de python
    //display_normalOrder(g);
    //display_naturalOrder(g);

    start = clock();
    DestruccionDelGrafo(g);
    end   = clock();
    total = (double)((end-start)/CLOCKS_PER_SEC);

    printf("Destruccion: %f\n",total);

    return 0;
}