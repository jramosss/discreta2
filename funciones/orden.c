#include <stdlib.h>
#include <stdio.h>
#include "../veinteveinte.h"

/* Ordena de Mayor a menor */
static int cmp_dec(const void *a, const void *b)
{
    u32 bs = *(u32 *)b;
    u32 as = *(u32 *)a;
    return (int)(bs - as);
}
/* Busca el grado en el arreglo ordenado naturalmente.
    Devuelve el idx N.
*/
static u32 buscar_index_N(u32 grado, u32 *ordeng, Grafo g){ 
    const u32 error = 4294967295;
    for (u32 i = 0; i < NumeroDeVertices(g); i++){              
        if (ordeng[i] == grado){
            u32 N = i;
            ordeng[i] = error;
            return N; 
        }
    }
    return error; 
}

/**
 * Ordena el arreglo principal, enfocado en sus grados, de mayor a menor. 
 * @param G el grafo 
 * @returns 0 si todo salio bien, 1 en caso contrario 
*/
char WelshPowell(Grafo G)
{
    const u32 error = 4294967295;
    const u32 nvertices = NumeroDeVertices(G);
    u32 N = 0;
    u32 *grados = calloc(nvertices, sizeof(u32));               // Arreglo grados para ordenar, contiene grados.
    u32 *grados_ordenados = calloc(nvertices, sizeof(u32));     // Arreglo de grados ordenados con respecto al arreglo de vertices ordenados
    if (grados == NULL || grados_ordenados == NULL) return 1;   // naturalmente de la estructura.

    for (u32 i = 0; i < nvertices; i++){                        // Llenamos ambos arreglos
        grados[i] = Grado(i, G);
        FijarOrden(i, G, i);                                    // Ordenamos los vertices de forma natural y llenamos el arreglo con los grados
        grados_ordenados[i] = Grado(i,G);                       // de dichos vertices
    }

    qsort(grados, nvertices, sizeof(u32), cmp_dec);

    for (u32 i = 0; i < nvertices; i++){                        // Por cada grado del arreglo grados, buscamos el indice al que refiere en el orden natural
        N = buscar_index_N(grados[i], grados_ordenados, G);
        if (N != error){
            FijarOrden(i, G, N);                                // Fijo los ordenes adecuadamente.
        } else {
            free(grados);
            free(grados_ordenados);
            grados = NULL;
            grados_ordenados = NULL;
            return 1;
        }
    }
    free(grados);
    free(grados_ordenados);
    grados = NULL;
    grados_ordenados = NULL;
    return 0;    
}

char RevierteBC(Grafo G)
{
    const u32 error = 4294967295;
    u32 N = 0;
    u32 nvertices = NumeroDeVertices(G);
    u32 *grados = calloc(nvertices, sizeof(u32));                   // arreglo grados para ordenar, contiene grados.
    u32 *ordeng = calloc(nvertices, sizeof(u32));                   // arreglo de orden natural, contiene grados.
    
    if (grados == NULL || ordeng == NULL) return 1;

    for (u32 i = 0; i < nvertices; i++){                        // Lleno ambos arreglos
        grados[i] = Color(i, G);
        FijarOrden(i, G, i);
        ordeng[i] = Color(i,G);
    }

    qsort(grados, nvertices, sizeof(u32), cmp_dec);

    for (u32 i = 0; i < nvertices; i++){
        N = buscar_index_N(grados[i], ordeng, G);
        if (N != error){
            FijarOrden(i, G, N);                                // Fijo los ordenes adecuadamente
        } else {
            free(grados);
            free(ordeng);
            grados = NULL;
            ordeng = NULL;
            return 1;
        }
    }
    free(grados);
    free(ordeng);
    grados = NULL;
    ordeng = NULL;
    return 0;
}   


/* Busca el grado en el arreglo ordenado naturalmente.
    Devuelve el idx N.
*/
static u32 find_idx(u32 obj, u32 *array, u32 cant){
    u32 N = 0;
    const u32 error = 4294967295;
    for (u32 i = 0; i < cant; i++){
        if (array[i] == obj){
            N = i;
            array[i] = error;
            return N;
        }
    }
    return error; 
}

char ChicoGrandeBC(Grafo G){
    u32 nvertices = NumeroDeVertices(G);
    u32 *colores = calloc(nvertices, sizeof(u32));              // Arreglo que voy a ordenar.
    u32 *grados = calloc(nvertices, sizeof(u32));               // Arreglo guia.
    if (colores != NULL && grados != NULL){
        const u32 error = 4294967295;

        for (u32 i = 0; i < nvertices; i++){
            FijarOrden(i, G, i);                                // como el de referencia.
            colores[i] = Color(i,G);                            // Lleno el arreglo de colores, tanto que que voy a ordenar
            grados[i] = Color(i, G);                            // Este ultimo ordenado de forma natural.
        }

        qsort(colores, nvertices, sizeof(u32), cmp_dec);

        u32 cant = colores[0] + 1;                              // Cantidad de colores con la que esta pintado G.

        u32 *card_grados = calloc(cant, sizeof(u32));           // Arreglo referencia que va a contener la cantidad de cada color.
        u32* card = calloc(cant, sizeof(u32));                  // Arreglo a ordenar
        if (card_grados != NULL && card != NULL){
            u32 c;
            
            for (u32 i = 0; i < nvertices; i++){
                c = grados[i];                                  // LLeno los arreglos contando la cantidad de veces que aparece
                card[c]++;                                      // el color i en grados.
                card_grados[c]++;   
            }
            
            qsort(card, cant, sizeof(u32), cmp_dec);            // Ordeno el arreglo cardinalidad, de mayor a menor.
            
            u32 idx;
            u32 flag = 0;
            u32 obj = 0;
            for (u32 i = 0; i < cant; i++){
                obj = card[i];                                  // extraigo de mayor a menor las cardinalidades.
                
                idx = find_idx(obj,card_grados, cant);          // Obtengo el color(idx)
                                                                // al que hace referencia dicha 
                                                                // cardinalidad.                                    
                if(idx != error){                   
                    for (u32 k = flag; k < (flag + obj); k++){
                        colores[k] = idx;                       // Vuelvo a ordenar, esta vez con los colores de mas card.
                    }
                    flag = flag + obj;                          // Me sirve para acordarme en que parte del arreglo quede la 
                                                                // ultima vez.
                
                } else {
                    free(colores);
                    free(grados);
                    free(card);
                    free(card_grados);
                    colores = NULL;
                    grados = NULL;
                    card = NULL;
                    card_grados = NULL;
                    return 1;
                }
            }

            u32 N = 0;
            for (u32 i = 0; i < nvertices; i++){
                N = find_idx(colores[i], grados, nvertices);    //obtengo el indice donde esta ese color en grados.

                if (N != error){
                    FijarOrden(i, G, N);                        // Reflejo todo los reordenes en el grafo.
                } else {
                    free(colores);
                    free(grados);
                    free(card);
                    free(card_grados);
                    colores = NULL;
                    grados = NULL;
                    card = NULL;
                    card_grados = NULL;
                    return 1;
                }
            }
            free(colores);
            free(grados);
            free(card);
            free(card_grados);
            colores = NULL;
            grados = NULL;
            card = NULL;
            card_grados = NULL;
            
            return 0;
        }
        free(colores);
        free(grados);
        colores = NULL;
        grados = NULL;
    }
    return 1;
}

/* Funcion auxiliar para aleatorizar vertices
    swapea la posicion i con una posicion aleatoria */
static void randomswaps(u32 *array, u32 n, u32 R){
    u32 al = 0;
    u32 tmp = 0;
    srand(R);
    u32 random = (u32)rand();
    for (u32 i = 0; i < n; i++){
        al = ((i+1) * R * random ) % n;
        tmp = array[i];
        array[i] = array[al];
        array[al] = tmp;
    }
}

char AleatorizarVertices(Grafo G, u32 R){
    u32 nvertices = NumeroDeVertices(G);
    u32 *guia = calloc(nvertices, sizeof(u32));    // Usamos este arreglo de guia para ordenar los vertices
    if(guia != NULL){
        /* Ordeno el arreglo principal de forma natural, para olvidarme del orden
            con el que llego el grafo
        */
        for (u32 i = 0; i < nvertices; i++){
            FijarOrden(i, G, i);
            guia[i] = i;                            // Array que voy a ordenar de forma aleatoria
        }

        randomswaps(guia, nvertices, R);            // Ordena el array de forma aleatoria dependiendo de R.

        for (u32 i = 0; i < nvertices; i++){        // De acuerdo al arreglo guia voy a reordenar el arreglo vertices de la estructura
            if(guia[i] < nvertices){
                FijarOrden(i, G, guia[i]);
            } else {
                free(guia);
                guia = NULL;
                return 1;
            }
        }
        free(guia);
        guia = NULL;
        return 0;
    }
    return 1;
}