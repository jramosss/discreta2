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

    printf("La construccion del grafo tardo %f segundos\n",(double)(end_t-start_t)/CLOCKS_PER_SEC);

    start_t = clock();

    Grafo C = CopiarGrafo(G);

    end_t = clock();

    printf("La copia del grafo tardo %f segundos\n",(double)(end_t-start_t)/CLOCKS_PER_SEC);

    check_eq(G->delta,C->delta,"Delta");
    check_eq(G->n,C->n,"N");
    check_eq(G->m,C->m,"M");
    
    bool flag = true;
    for (u32 i = 0; i < G->n; i++) {
        flag = check_vert(G->orden_natural[i],C->orden_natural[i]);
        if (!flag) break;
    }
    check_cond((char)flag,"Los arreglos de orden natural son iguales",
                          "Los arreglos de orden natural no son iguales");
    //check_cond(check_vert(G->raiz,C->raiz),"Las raices son iguales","Las raices no son iguales");

    for (u32 i = 0; i < G->n; i++) {
        flag = check_vert(G->vertices[i],C->vertices[i]);
        if (!flag) break;
    }

    check_cond((char)flag,"Los arreglos de vertices son iguales",
                          "Los arreglos de vertices no son iguales");
}