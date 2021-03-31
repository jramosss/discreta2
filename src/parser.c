#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "utils.h"
#include "hash.h"

/**
 * Esta funcion acomoda el puntero del fichero para empezar a leer las etiquetas "e x y"
 * @param fp fichero donde vamos a acomodar el puntero
 *  PD: Para ahora codigo podriamos eliminarla, y usar el num_lados_vertices() para acomodar el     puntero
*/
static void acomodar_puntero (FILE *fp) {
    char palabra1[MAXCHAR];                             // Buscaremos el valor "p"
    char palabra2[MAXCHAR];                             // Buscaremos el valor "edge"
    char vertices[MAXCHAR];
    char lados[MAXCHAR];
    
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

/* Initialize a vert */
Vert *vert_create (u32 name, u32 mlados) {
    Vert *newvert = calloc(1, sizeof(struct Vert));
    newvert->vecinos = calloc(mlados, sizeof(Vert*));
    newvert->nombre = name;
    newvert->index = name;
    newvert->grado = 0;
    newvert->color = error;
    return newvert;
}

/* Setea en el grafo los valores n y m */
void num_lados_vertices (FILE *fp, Grafo g) {
    char palabra1[MAXCHAR];                             // Buscaremos el valor "p"
    char palabra2[MAXCHAR];                             // Buscaremos el valor "edge"
    char vertices[MAXCHAR];
    char lados[MAXCHAR];
    
    fscanf(fp, "%1s", palabra1);
    while (!feof(fp)) {
        if (memcmp(palabra1,"c",2)==0) {
            fscanf(fp, "%[^\n]", palabra1);             // Ignorar los comentarios
            fscanf(fp, "%1s", palabra1);
        } else if (memcmp(palabra1,"p",2)==0){
            fscanf(fp, "%*s %s %s", vertices, lados);
            g->n = (u32)atoi(vertices);  
            g->m = (u32)atoi(lados);
            fseek(stdin,0,SEEK_SET);
            break;
        } else {
            fscanf(fp, "%[^\n]", palabra1);
            fscanf(fp, "%1s", palabra1);
        }
    }
}

/* Agrega a la lista de vecinos de "vert" el vertice "vecino", y retorna el nuevo grado del vertice "vert" */
static u32 agregar_vecino(Vert *vert, Vert *vecino){
    return 0;
}


/* Dados 2 grados y el delta actual, si el mayor grado supera al delta se reemplaza. */
static u32 actualizar_delta(u32 gradox, u32 gradoy, u32 delta) {

    if (gradox > gradoy){
        if (gradox > delta) {
            return gradox;    
        } else {
            return delta;
        }
    } else {
        if (gradoy > delta) {
            return gradoy; 
        } else {
            return delta;
        }
    }
}

/* Esta funcion llena el arreglo vertices con el orden dado, y genera el arreglo con orden natural. */
void fill_verts(FILE *fp, Grafo G) {
    char e[MAXCHAR];
    char xs[MAXCHAR];
    char ys[MAXCHAR];
    u32 pos = 0;   // Esta variable hacer referencia a la posicion de un vertice x en el grafo.txt
    u32 x = 0;
    u32 y = 0;
    u32 delta = 0;
    u32 gradox = 0;
    u32 gradoy = 0;
    acomodar_puntero(fp);

    // Creo la tabla hash

    Hash_table *hash = crear_tabla(G->n);

    for (u32 i = 0; i < G->m; i++) {
        fscanf(fp, "%*s %s %s", xs, ys);
        x = (u32)atoi(xs);
        y = (u32)atoi(ys);
        u32 pos_deX_enHash = hash_key(x,G->n);
        u32 pos_deY_enHash = hash_key(y,G->n);

        u32 esta_x = buscar_vertice_en_hash(pos_deX_enHash,x,hash);
        u32 esta_y = buscar_vertice_en_hash(pos_deY_enHash,y,hash);
        
        if (!esta_x && !esta_y) {
            Vert *vx = vert_create(x,G->m);
            Vert *vy = vert_create(y,G->m);
            agregar_vertice(vx,pos_deX_enHash,hash);
            agregar_vertice(vy,pos_deY_enHash,hash);
            G->vertices[pos] = vx;
            G->vertices[pos+1] = vy;
            pos = pos + 2;

        } else if (!esta_x && esta_y) {
            Vert *vx = vert_create(x,G->m);
            agregar_vertice(vx,pos_deX_enHash,hash);
            G->vertices[pos] = vx;
            pos++;

        } else if (esta_x  && !esta_y) {
            Vert *vy = vert_create(y,G->m);
            agregar_vertice(vy,pos_deY_enHash,hash);
            G->vertices[pos] = vy;
            pos++;
        }
    }

    G->delta = delta;

    fseek(stdin,0,SEEK_SET);
    
}



