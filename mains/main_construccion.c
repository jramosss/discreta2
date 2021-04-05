#include "../RomaVictor.h"

inline static u32 grafo_muy_grande (u32 n) {
    return n > 100;
}

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
    //if (!grafo_muy_grande(g->n))
      //  display_normalOrder(g);
    printf("\nVertices %u, Lados %u\n", g->n, g->m);
    printf("2do Vert: %u\n", g->vertices[2]->nombre);
    printf("\nEl delta del grafo es: %u\n", g->delta);

    DestruccionDelGrafo(g);

    return 0;
}