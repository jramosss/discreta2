#ifndef __UTILS_H__
#define __UTILS_H__
#include "../RomaVictor.h"        //No se si esto es necesario

#define blank(k) printf("\n")

#define error 4294967295
#define MAXCHAR 100000

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
char hayMlineas             (FILE *fp, u32 mlineas);
void acomodar_puntero       (FILE *fp);

#endif