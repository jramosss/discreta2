#include "../veinteveinte.h"

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


int main(void) {
    Grafo g = ConstruccionDelGrafo();
    printf("\nVertices %d Lados %d\n", g->n, g->m);
    printf("2vert: %d\n", g->vertices[2]->nombre);
    printf("\nContenido de vertices[2]: %d\n", g->vertices[2]);
    display_normalOrder(g);
    display_naturalOrder(g);
    return 0;
}