#include "../RomaVictor.h";
#include "utils.h";

u32 Greedy(Grafo G) {
/* 
    Cotas para greedy
    X(G) <= Delta + 1.
    Si G es conexo, entonces X(G) <= Delta, a menos que G sea un ciclo impar o un grafo completo.
*/  
    u32 colorsQty = 0;
    u32 maxColors = Delta(G) + 1;
    char *usedColors = calloc(maxColors, sizeof(char));
    u32 *visitados = calloc(NumeroDeVertices(G), sizeof(u32));
    if (visitados == NULL || usedColors == NULL) return error;

    // Pinto al primer vertice con 0 y incremento la cantidad de colores.
    FijarColor(0, 0, G);
    visitados[0] =  1;
    colorsQty++;

    
    //Luego por cada vertice, siempre intento pintar con el menor color posible.
    for (u32 i = 1; i < NumeroDeVertices(G); i++) {

        // reset a los colores usados por los vecinos.
        memset(usedColors, 0, maxColors);
        u32 color = error;
        for (u32 j = 0; j < i; j++) {
            
            //para cada vecino visitado seteo su color como usado.
            if (visitados[OrdenVecino(j, i, G)] == 1) {
                
                color = ColorVecino(j, i, G);
                usedColors[color] = 1;
            }
        }

        /*  Luego busco segun la cantidad de colores que utilice hasta el
            momento en usedColors resultante, El menor color posible para
            colorear el vertice.
        */
        color = error;
        for (i = 0; i < colorsQty; i++) {

            if (usedColors[i] == 0) {

                color = i;
                break;
            }
        }

        /*  Checkeo si tengo que utilizar un nuevo color. 
            De ser asi aumento colorsQty 
        */
        if(color == error) {

            color = colorsQty;
            colorsQty++;
        }
        /*  Una vez encontrado el minimo color para el vertice i, lo pinto y lo
            guardo en visitados.
        */
        FijarColor(color, i, G);
    }

    return colorsQty;
}