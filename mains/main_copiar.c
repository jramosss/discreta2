#include <stdbool.h>
#include <stdio.h>
#include "time.h"
#include "../RomaVictor.h"
#include "../src/utils.h"

//Solo checkea los atributos, no los vecinos

inline static bool check_vert_aux (Vert* v,Vert* b){
    return (v->color == b->color && v->grado == b->grado &&
            v->index == b->index && v->nombre == b->nombre);
}

static bool check_vecinos (Vert* v,Vert* b) {
    if (v->grado != b->grado) return false;

    for (u32 i = 0; i < v->grado; i++) {
        // printf("Vecino %u / %u\n", i, v->grado-1);
        // printf("El vecino del original %u es %u\n",v->nombre,v->vecinos[i]->nombre);
        // printf("  |   El vecino de la copia %u es %u\n",b->nombre,b->vecinos[i]->nombre);
        if (!check_vert_aux(v->vecinos[i],b->vecinos[i]))
            return false;
    }

    return true;
}

static bool check_vert (Vert* v,Vert* b) {
    return (v->color == b->color && v->grado == b->grado &&
            v->index == b->index && v->nombre == b->nombre &&
            check_vecinos(v,b));
}

int main (void) {
    clock_t start_t, end_t; 
    start_t = clock();

    Grafo G = ConstruccionDelGrafo();

    end_t = clock();

    blank(1);

    //Time construction Took
    printf("%f\n",(double)(end_t-start_t)/CLOCKS_PER_SEC);

    start_t = clock();

    Grafo C = CopiarGrafo(G);

    end_t = clock();

    //Time copy took
    printf("%f\n",(double)(end_t-start_t)/CLOCKS_PER_SEC);

    printf(G->delta == C->delta ? "Los campos delta son iguales\n": "Los campos delta NO son iguales\n");

    printf(G->n == C->n ? "Los campos N son iguales\n": "Los campos N NO son iguales\n");

    printf(G->m == C->m ? "Los campos M son iguales\n" : "Los campos M NO son iguales\n");
    
    
    bool flag = true;
    for (u32 i = 0; i < G->n; i++) {
        flag = check_vert(G->orden_natural[i],C->orden_natural[i]);
        if (!flag) break;
    }
    printf(flag ?         "Los campos orden natural son iguales\n" :
                          "Los campos orden natural NO son iguales\n");

    for (u32 i = 0; i < G->n; i++) {
        flag = check_vert(G->vertices[i],C->vertices[i]);
        if (!flag) break;
    }

    printf(flag ?         "Los campos vertices son iguales\n" :
                          "Los campos vertices NO son iguales\n");

    DestruccionDelGrafo(C);
    DestruccionDelGrafo(G);
}