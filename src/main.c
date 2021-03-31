#include "../RomaVictor.h"

static void display_naturalOrder (Grafo G){
    printf("\nVertices orden natural: [");
    for(u32 i = 0; i < (G->n); i++){
        printf("%d,",G->orden_natural[i+1]->nombre);
    }
    printf("]\n");
}

static void display_normalOrder (Grafo G){
    printf("\nVertices orden normal: [");
    for(u32 i = 0; i < (G->n); i++){
        printf("%d,",G->vertices[i]->nombre);
    }
    printf("]\n");
}


int main (){
    const Grafo G = ConstruccionDelGrafo();

    printf("n = %u\n", G->n);
    printf("m = %u\n", G->m);
    printf("delta = %u\n", G->delta);

    printf("\n=================Grados=================\n");
    printf("vertice %u\n", G->vertices[0]->nombre);
    G->vertices[0]->grado == 71 ? printf("TRUE"): printf("FALSE");
    
    u32 max = 0;
    for(u32 i = 0; i < G->n; i++){
        if(G->vertices[i]->grado > max) {
            max = G->vertices[i]->grado;
        }
    }

    printf("\n=================Delta=================\n");
    printf("Delta es %u\n", G->delta);
    G->delta == max ? printf("True\n") : printf("False: el max grado es %u\n", max);
}