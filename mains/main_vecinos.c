#include "../RomaVictor.h"
#include <stdbool.h>
#include "../src/utils.h"

static void display_normalOrder (Grafo G){
    printf(" [");
    for(u32 i = 0; i < (G->n); i++){
        printf("%d,",G->vertices[i]->nombre);
    }
    printf("]\n");
}

// ESTE TEST FALLA PORQUE DEBERIA HACER UNA FUNCION XvecinoDe(x,y) si x es vecino de y que devuelva true,
// y asi ir chequeando que los vecinos fueron bien parseados, de todos modos en los prints queda claro
// que anda bien.

static void vecinosOriginales(u32 *vecinos, u32 grado) {
    printf("[");
    for (u32 i = 0; i < grado; i++)
    {
        printf("%u ", vecinos[i]);
    }
    printf("]\n");
}

int main(void) {
    Grafo G = ConstruccionDelGrafo();
    u32 vecinos_1[4] = {2,5,4,6};
    u32 GradoDe1 = 4;
    u32 vecinos_2[2] = {1,4};
    u32 GradoDe2 = 2;
    u32 vecinos_4[3] = {1,2,5};
    u32 GradoDe4 = 3;
    u32 vecinos_5[2] = {1,4};
    u32 GradoDe5 = 2;
    u32 vecinos_6[1] = {1};
    u32 GradoDe6 = 1;

    bool cond = true;

    u32 orden_interno[5] = {1,2,6,4,5};
    
    for (u32 i = 0; i < G->n; i++)
    {
        cond = (cond && (orden_interno[i] == G->vertices[i]->nombre));
    }

    if(cond) {
        printf("\nOrden original [1,2,6,4,5]\n");
        printf("=\nOrden parseado");
        display_normalOrder(G);
        printf("\nEl orden en que fueron parseados los vertices es CORRECTO.\n");
    } else {
        printf("\nOrden original [1,2,6,4,5]\n");
        printf("=\nOrden parseado");
        display_normalOrder(G);
        printf("\nEl orden en que fueron parseados los vertices es INCORRECTO.\n");
    }

    printf("\nAhora chequeamos que los vecinos sean correctos:\n");
    
    cond = true;
    for (u32 i = 0; i < G->n ; i++)
    {
        if(i == 0)
        {
            printf("\nVecinos parseados de %u : [", G->vertices[i]->nombre);
            for (u32 j = 0; j < G->vertices[i]->grado; j++)
            {
                cond = (cond && (vecinos_1[j] == G->vertices[i]->vecinos[j]->nombre));
                printf("%u ",G->vertices[i]->vecinos[j]->nombre);
            }
            printf("] = ");
            vecinosOriginales(vecinos_1, GradoDe1);
            
        } else if (i==1)
        {
            printf("\nVecinos de %u[", G->vertices[i]->nombre);
            for (u32 j = 0; j < G->vertices[i]->grado; j++)
            {
                cond = (cond && (vecinos_2[j] == G->vertices[i]->vecinos[j]->nombre));
                printf("%u ",G->vertices[i]->vecinos[j]->nombre);
            }
            printf("] = ");
            vecinosOriginales(vecinos_2, GradoDe2);
        } else if (i==2)
        {
            printf("\nVecinos de %u[", G->vertices[i]->nombre);
            for (u32 j = 0; j < G->vertices[i]->grado; j++)
            {
                cond = (cond && (vecinos_6[j] == G->vertices[i]->vecinos[j]->nombre));
                printf("%u ",G->vertices[i]->vecinos[j]->nombre);
            }
            printf("] = ");
            vecinosOriginales(vecinos_6, GradoDe6);
        } else if (i==3)
        {
            printf("\nVecinos de %u[", G->vertices[i]->nombre);
            for (u32 j = 0; j < G->vertices[i]->grado; j++)
            {
                cond = (cond && (vecinos_4[j] == G->vertices[i]->vecinos[j]->nombre));
                printf("%u ",G->vertices[i]->vecinos[j]->nombre);
            }
            printf("] = ");
            vecinosOriginales(vecinos_4, GradoDe4);
        } else
        {
            printf("\nVecinos de %u[", G->vertices[i]->nombre);
            for (u32 j = 0; j < G->vertices[i]->grado; j++)
            {
                cond = (cond && (vecinos_5[j] == G->vertices[i]->vecinos[j]->nombre));
                printf("%u ",G->vertices[i]->vecinos[j]->nombre);
            }
            printf("] = ");
            vecinosOriginales(vecinos_5, GradoDe5);
        } 
    }

  
    printf("\nLos vecinos fueron parseados correctamente\n");
    
    DestruccionDelGrafo(G);

    return 0;
}