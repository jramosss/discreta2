#ifndef __UTILS_H__
#define __UTILS_H__
#include "../RomaVictor.h"        //No se si esto es necesario
#include <stdbool.h>

#define blank(k) printf("\n")

#define error 4294967295
#define MAXCHAR 100000

#define pass (void)0

#define section (msg) printf("\n\n\n====================%s====================\n\n\n",msg);

typedef struct lightVert {
    u32 index;
    u32 color;
}lightVert;

void print_in_red           (char*);
void print_in_green         (char*);
void print_arr              (u32*,u32);
void check_cond             (char cond,char* affirmative_msg,char* negative_msg);
void check_alv              (char alv);
void check_wp               (char wp);
void check_chicogrande      (char cgbc);
void check_coloreo_propio   (char cond);
void check_sc               (char sw);
void check_bipartito        (char bip);
Vert* find_vert_by_index    (u32,Grafo);
u32 hayMlineas              (FILE *fp, u32 mlineas);
u32 acomodar_puntero        (FILE *fp);
int compare                 (const void*, const void*);
void print_arr_vertices     (Grafo);
int  cmpfunc                (const void*, const void*);
void swap                   (u32*, u32*);
int  vert_cmp               (const void*,const void*);
int  color_cmp              (const void*, const void*);

#endif