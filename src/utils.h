#ifndef __UTILS_H__
#define __UTILS_H__
#include "../RomaVictor.h"        //No se si esto es necesario
#include <stdbool.h>

#define blank(k) printf("\n")

#define error 4294967295
#define MAXCHAR 100000

#define pass (void)0

#define section(msg) printf("\n\n\n============================%s=============================\n\n\n",msg)

void print_in_red           (char*);
void print_in_green         (char*);
void check_cond             (char,char*,char*);
void check_bipartito        (char);
void check_sc               (char);
void check_coloreo_propio   (char);
void check_chicogrande      (char);
void check_wp               (char);
void check_alv              (char);
void check_eq               (u32,u32,char*);
void print_arr              (u32*,u32);
Vert* find_vert_by_index    (u32,Grafo);
u32 hayMlineas             (FILE *fp, u32 mlineas);
u32 acomodar_puntero       (FILE *fp);
int compare                 (const void*, const void*);
//Le asigna al arreglo de vertices el orden del arreglo de orden natural
void assign_natural_order   (Grafo);
void print_arr_vertices     (Grafo);
bool arr_contains           (u32*,u32,u32);
int  cmpfunc                (const void*, const void*);
void swap                   (u32*, u32*);
int  vert_cmp               (const void*,const void*);

#endif