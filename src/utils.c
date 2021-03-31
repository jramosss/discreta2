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
Vert* find_vert_by_index (u32 i, Grafo G)
{
    return G->vertices[i];
}