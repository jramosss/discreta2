#include "../RomaVictor.h"
#include <stdbool.h>
#include "../src/utils.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();
    bool cond = true;
    u32 vertice_i = 0;
    u32 vecino_j = 1;
    u32 peso_inicial = PesoLadoConVecino(vecino_j,vertice_i, G);
    u32 peso_k = 55;
    u32 res_fijar = 0;

    printf("\n [*] Chequeamos el peso inicial del iesimo vertice %u con su jesimo vecino %u [*] \n", vertice_i, vecino_j);
    
    if(vertice_i > G->n || vecino_j > G->vertices[vertice_i]->grado) {
        cond = (peso_inicial == error);
        check_cond((char)cond,"La funcion devolvio error correctamente.",
                            "La funcion siguio la ejecucion, deberia haber arrojado error.");
    } else {
        cond = (peso_inicial == 0);
        check_cond((char)cond,"Efectivamente el peso inicial es 0.",
                            "El peso inicial no es 0.");
    }

    printf("\n [*] Asignamos el peso %u al lado anterior (%u,%u) [*] \n", peso_k,vertice_i,vecino_j);
    res_fijar = FijarPesoLadoConVecino(vecino_j,vertice_i,peso_k,G);

    if(vertice_i > G->n || vecino_j > G->vertices[vertice_i]->grado) {
        cond = (res_fijar == error);
        check_cond((char)cond,"La funcion devolvio error correctamente.",
                            "La funcion siguio la ejecucion, deberia haber arrojado error.");
    } else {
        cond = (PesoLadoConVecino(vecino_j,vertice_i,G) == peso_k);
        check_cond((char)cond,"El peso entre los lados es el correcto.",
                            "El peso no se seteo correctamente");
    }

    DestruccionDelGrafo(G);

    return 0;
}