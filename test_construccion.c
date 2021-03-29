#include "./RomaVictor.h";

int main (){
    const Grafo G = ConstruccionDelGrafo();

    printf("n = %u\n", G->n);
    printf("m = %u\n", G->m);
    printf("delta = %u\n", G->delta);

    printf("[");
    for(int i = 0; i < G->n; i++) {
        if(i < G->n - 1) {
            printf("%u, ", G->vertices[i]->nombre);
        } else { 
            printf("%u", G->vertices[i]->nombre);
        }
    }
    printf("]");

    printf("=================Grados=================\n");
    printf("vertice %u\n", G->vertices[0]->nombre);
    G->vertices[0]->grado == 71 ? printf("TRUE"): printf("FALSE");
    
    u32 max = 0;
    for(u32 i = 0; i < G->n; i++){
        if(G->vertices[i]->grado > max) {
            max = G->vertices[i]->grado;
        }
    }

    printf("=================Grados=================\n");
    printf("Delta es %u\n", G->delta);
    G->delta == max ? printf("True") : printf("False");
}