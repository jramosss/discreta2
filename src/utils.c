#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"
#include "../RomaVictor.h"

void print_in_red (char* msg) {
    printf("\033[0;31m");
    printf("%s\n",msg);
    printf("\033[0m");
}

void print_in_green (char*msg) {
    printf("\033[0;32m");
    printf("%s\n",msg); 
    printf("\033[0m");
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

void check_cond (char cond,char* affirmative_msg,char* negative_msg) {
    cond ? print_in_green(affirmative_msg) : print_in_red(negative_msg);
}

void check_bipartito (char bip) {
    check_cond(bip,"El grafo es bipartito","El grafo no es bipartito");
}

//Check aleatorizar Vertices
void check_alv (char alv) {
    check_cond(alv, "BIEN:AleatorizarVertices","ERROR: AleatorizarVertices");
}

void section (char* msg) {
    printf("\n\n\n====================%s====================\n\n\n",msg);
}

/**
 * Esta funcion acomoda el puntero del fichero para empezar a leer las etiquetas "e x y"
 * @param fp fichero donde vamos a acomodar el puntero
 *  PD: Para ahora codigo podriamos eliminarla, y usar el num_lados_vertices() para acomodar el     puntero
*/
u32 acomodar_puntero (FILE *fp) {
    char palabra1[MAXCHAR];                             // Buscaremos el valor "p"
    char vertices[MAXCHAR];
    char lados[MAXCHAR];
    int  ignore_me = 0;
    //const long unsigned int lines = 2;
    
    fseek(stdin,0,SEEK_SET);

    while (!feof(fp)) {
        ignore_me = fscanf(fp, "%1s", palabra1);
        if (memcmp(palabra1,"c",2)==0) {
            ignore_me = fscanf(fp, "%[^\n]", palabra1);             // Ignorar los comentarios
            printf("\n%s\n", palabra1);
        } else if (memcmp(palabra1,"p",2)==0){
            ignore_me = fscanf(fp, "%s", palabra1);
            if (memcmp(palabra1,"edge",5)==0) {
                ignore_me = fscanf(fp, "%s", vertices);
                ignore_me = fscanf(fp, "%s", lados);
                printf("\n%s %s\n", vertices, lados);
                return 0;
            }
        } else {
            ignore_me = fscanf(fp, "%[^\n]", palabra1);
            printf("\n%s\n", palabra1);
        }
    }
    if (ignore_me) pass;
    return 1;
}

u32 hayMlineas(FILE *fp, u32 mlineas) {
    char xs[MAXCHAR];
    char ys[MAXCHAR];
    u32 lineas = 0;
    int ignore_me = 0;

    acomodar_puntero(fp);

    while(!feof(fp)) {
        ignore_me = fscanf(fp, "%*s %s %s", xs, ys);
        lineas++;
    }
    if (ignore_me) pass;
    return (lineas >= mlineas ? 1 : 0);
}

int compare(const void *_a, const void *_b) {
    int *a, *b;
    
    a = (int *) _a;
    b = (int *) _b;
    
    return (*a - *b);
}

void print_arr_vertices (Grafo G) {
    printf("[");
    for (u32 i = 0; i < NumeroDeVertices(G); i++) 
        printf(i == NumeroDeVertices(G)-1 ? "%u" : "%u,",Nombre(i,G));
    printf("]\n");
}

void print_arr_colores (Grafo G) {
    printf("[");
    for (u32 i = 0; i < NumeroDeVertices(G); i++) 
        printf(i == NumeroDeVertices(G)-1 ? "%u" : "%u,",Color(i,G));
    printf("]\n");
}

int cmpfunc(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void swap(u32 *xp, u32 *yp) {
    u32 temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int vert_cmp (const void* a,const void* b) {
    Vert *xs = *(struct Vert **)a;
    Vert *ys = *(struct Vert **)b;
    return (xs->nombre - ys->nombre);
}

u32* generate (u32 n) {
    u32* array = malloc(n*sizeof(u32));
    for (u32 i = 0; i < n; i++)
        array[i] = i;

    return array;
}

u32* etareneg (u32 n) {
    u32* array = malloc(n*sizeof(u32));
    int j = 0;
    for (u32 i = 0; i < n; i++) {
        array[j] = (n-1)-i;
        j++;
    }

    return array;
}

u32* eswap (u32 n,u32 e,u32 seed) {
    u32* array = etareneg(n);
    srand(seed);
    u32 ran = (u32)rand() % e;
    
    for (u32 i = 0; i < n; i++)
        if (ran == (u32)rand() % e)
            swap(&array[i],&array[(u32)rand() % n]);

    return array;
}

u32* generateAndShuffle (u32 n,u32 seed) {
    u32* arr = generate(n);
    srand(seed);

    for (u32 i = 0; i < n; i++) {
        u32 randd = (u32)rand() % n;
        while (randd == i)
            randd = (u32)rand() % n;
        swap(&arr[i],&arr[randd]);
    }

    return arr;
}