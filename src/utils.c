#include <stdio.h>
#include "utils.h"
#include "../RomaVictor.h"

void print_in_red (char* msg) {
    printf("\033[0;31m"); //Set the text to the color red
    printf("%s\n",msg); //Display Hello in red
    printf("\033[0m"); //Resets the text to default color
}

void print_in_green (char*msg) {
    printf("\033[0;32m"); //Set the text to the color red
    printf("%s\n",msg); //Display Hello in red
    printf("\033[0m"); //Resets the text to default color
}

void check_cond (char cond,char* affirmative_msg,char* negative_msg) {
    cond ? print_in_green(affirmative_msg) : print_in_red(negative_msg);
}

void check_bipartito (char bip) {
    check_cond(bip == '1',"El grafo es bipartito","El grafo no es bipartito");
}

//Check Switch Colores
void check_sc (char sw) {
    check_cond(sw == '0', "BIEN: SwitchColores","ERROR SwitchColores");
}

void check_coloreo_propio (char cond) {
    check_cond(cond , "El coloreo es propio","El coloreo no es propio");
}

void check_chicogrande (char cgbc) {
    check_cond(cgbc == '0', "BIEN:ChicoGrande","ERROR: ChicoGrande");
}

//Check welshpowell
void check_wp (char wp) {
    check_cond(wp == '0' , "BIEN:WelshPowel","ERROR: WelshPowel");
}

//Check aleatorizar Vertices
void check_alv (char alv) {
    check_cond(alv == '0', "BIEN:AleatorizarVertices","ERROR: AleatorizarVertices");
}

/**
 * @param i Un indice
 * @param G Un grafo
 * @returns El vertice en el indice indicado
*/
Vert* find_vert_by_index (u32 i, Grafo G) {
    return G->vertices[i];
}

void check_eq (u32 x, u32 y,char* campo) {
    if (x == y) {
        printf("\033[0;32m"); //Set the text to the color red
        printf("Los campos %s son iguales\n",campo); //Display Hello in red
        printf("\033[0m"); //Resets the text to default color
    }
    else {
        printf("\033[0;31m"); //Set the text to the color red
        printf("Los campos %s no son iguales\n",campo); //Display Hello in red
        printf("\033[0m"); //Resets the text to default color
    }
}

void print_arr (u32* arr,u32 len) {
    printf("[");
    for (u32 i = 0; i < len; i++) {
        if (i == len-1)
            printf("%u",arr[i]);
        else
            printf("%u,",arr[i]);
    }
    printf("]\n");
}

/**
 * Esta funcion acomoda el puntero del fichero para empezar a leer las etiquetas "e x y"
 * @param fp fichero donde vamos a acomodar el puntero
 *  PD: Para ahora codigo podriamos eliminarla, y usar el num_lados_vertices() para acomodar el     puntero
*/
void acomodar_puntero (FILE *fp) {
    char palabra1[MAXCHAR];                             // Buscaremos el valor "p"
    char palabra2[MAXCHAR];                             // Buscaremos el valor "edge"
    char vertices[MAXCHAR];
    char lados[MAXCHAR];
    
    fseek(stdin,0,SEEK_SET);

    fscanf(fp, "%1s", palabra1);
    while (!feof(fp)) {
        if (memcmp(palabra1,"c",2)==0) {
            fscanf(fp, "%[^\n]", palabra1);             // Ignorar los comentarios
            fscanf(fp, "%1s", palabra1);
        } else if (memcmp(palabra1,"p",2)==0){
            fscanf(fp, "%*s %s %s", vertices, lados);
            break;
        } else {
            fscanf(fp, "%[^\n]", palabra1);
            fscanf(fp, "%1s", palabra1);
        }
    }
}

char hayMlineas(FILE *fp, u32 mlineas) {
    char xs[MAXCHAR];
    char ys[MAXCHAR];
    u32 lineas = 0;

    acomodar_puntero(fp);

    while(!feof(fp)) {
        fscanf(fp, "%*s %s %s", xs, ys);
        lineas++;
    }

    return (lineas >= mlineas ? '1' : '0');
}