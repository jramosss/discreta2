#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "utils.h"
#include "hash.h"


/** Crea el vertice nombre "name" con el index "index"
 * @param name nombre del vertice
 * @param index index del vertice
 */
Vert *vert_create (u32 name, u32 index) {
    Vert *newvert = calloc(1, sizeof(struct Vert));
    newvert->vecinos = NULL;
    newvert->nombre = name;
    newvert->index = index;
    newvert->grado = 0;
    newvert->color = error;
    return newvert;
}

/* Setea en el grafo los valores n y m */
u32 num_lados_vertices (FILE *fp, Grafo g) {
    char palabra1[MAXCHAR];                             // Buscaremos el valor "p"
    char vertices[MAXCHAR];
    char lados[MAXCHAR];
    //Just to prevent warnings
    int  ignore_me = 0;
    
    while (!feof(fp)) {
        ignore_me = fscanf(fp, "%1s", palabra1);
        if (memcmp(palabra1,"c",2)==0) {
            ignore_me = fscanf(fp, "%[^\n]", palabra1);             // Ignorar los comentarios
        } else if (memcmp(palabra1,"p",2)==0){
            ignore_me = fscanf(fp, "%s", palabra1);
            if (memcmp(palabra1,"edge",5)==0) {
                ignore_me = fscanf(fp, "%s", vertices);
                ignore_me = fscanf(fp, "%s", lados);
                g->n = (u32)atoi(vertices);  
                g->m = (u32)atoi(lados);
                return 1;
            }
        } else {
            ignore_me = fscanf(fp, "%[^\n]", palabra1);
        }
    }
    return 0;
    //To prevent warnings
    if (ignore_me) pass;
}

/* Agrega a la lista de vecinos de "vert" el vertice "vecino", y retorna el nuevo grado del vertice "vert" */
/*
static u32 agregar_vecino(Vert *vert, Vert *vecino){
    return 0;
}*/


/* Dados 2 grados y el delta actual, si el mayor grado supera al delta se reemplaza. */
static u32 actualizar_delta(u32 gradox, u32 gradoy, u32 delta) {
    if (gradox > gradoy)
        return gradox > delta ? gradox : delta;
     else
        return gradoy > delta ? gradoy : delta;
}

/**
 * A medida que se agregan vecinos, esta funcion 
tambien actualiza los iesimo pesolado del vertice x al vertice x->vecinos[i], 
reallocando su arreglo*/
static void actualizar_pesoslados(Vert *x) {
    if((x->grado - 1) == 0) {
        x->pesoslados = calloc(1, sizeof(u32*));
        x->pesoslados[x->grado-1] = 0;
    } else {
        x->pesoslados = realloc(x->pesoslados,x->grado *sizeof(u32*));
        x->pesoslados[x->grado-1] = 0;
    }
}

/**
 * Esta funcion agrega el vecino "y" al vertice "x"
 * @param x vertice al que se le agrega el nuevo vecino
 * @param y vecino a agregar
*/
static void agregar_vecino(Vert *x, Vert *y) {
    if(x->grado == 0){
        x->grado++;
        x->vecinos = calloc(1, sizeof(Vert*));
        x->vecinos[x->grado - 1] = y;
    } else {
        x->grado++;
        x->vecinos = realloc(x->vecinos, x->grado * sizeof(Vert*));
        x->vecinos[x->grado - 1] = y;
    }
}

/* Esta funcion llena el arreglo vertices con el orden dado, y genera el arreglo con orden natural. */
u32 fill_verts(FILE *fp, Grafo G) {
    char xs[MAXCHAR];
    char ys[MAXCHAR];
    u32 pos = 0;   // Esta variable hacer referencia a la posicion de un vertice x en el grafo.txt
    u32 x = 0;
    u32 y = 0;
    u32 delta = 0;
    u32 lineas = 0;
    //u32 puntero_acomodado = acomodar_puntero(fp);

    // Creo la tabla hash

    Hash_table *hash = crear_tabla(G->n);

    while(!feof(fp)) {
        //To prevent warnings
        if (fscanf(fp, "%*s %s %s", xs, ys)) pass;
        lineas++;
        x = (u32)atoi(xs);
        y = (u32)atoi(ys);
        u32 pos_deX_enHash = hash_key(x,G->n);
        u32 pos_deY_enHash = hash_key(y,G->n);

        Vert *esta_x = buscar_vertice_en_hash(pos_deX_enHash,x,hash);
        Vert *esta_y = buscar_vertice_en_hash(pos_deY_enHash,y,hash);
        
        if (esta_x == NULL && esta_y == NULL) {
            Vert *vx = vert_create(x, pos);
            Vert *vy = vert_create(y, pos+1);

            agregar_vecino(vx,vy);
            agregar_vecino(vy,vx);

            actualizar_pesoslados(vx);
            actualizar_pesoslados(vy);

            agregar_vertice(vx,pos_deX_enHash,hash);
            agregar_vertice(vy,pos_deY_enHash,hash);
            G->vertices[pos] = vx;
            G->vertices[pos+1] = vy;
            G->orden_natural[pos] = vx;
            G->orden_natural[pos+1] = vy;
            pos = pos + 2;

        } else if (esta_x == NULL) {
            Vert *vx = vert_create(x,pos); agregar_vecino(vx,esta_y);
            agregar_vecino(esta_y,vx);

            delta = actualizar_delta(vx->grado, esta_y->grado, delta);

            actualizar_pesoslados(vx);
            actualizar_pesoslados(esta_y);

            agregar_vertice(vx,pos_deX_enHash,hash);
            G->vertices[pos] = vx;
            G->orden_natural[pos] = vx;
            pos++;

        } else if (esta_y == NULL) {
            Vert *vy = vert_create(y,pos);
            agregar_vecino(esta_x,vy);
            agregar_vecino(vy,esta_x);

            delta = actualizar_delta(esta_x->grado, vy->grado, delta);

            actualizar_pesoslados(esta_x);
            actualizar_pesoslados(vy);

            agregar_vertice(vy,pos_deY_enHash,hash);
            G->vertices[pos] = vy;
            G->orden_natural[pos] = vy;
            pos++;

        } else {agregar_vecino(esta_x,esta_y);
            agregar_vecino(esta_y,esta_x);

            delta = actualizar_delta(esta_x->grado, esta_y->grado, delta);

            actualizar_pesoslados(esta_x);
            actualizar_pesoslados(esta_y);
        }
    }
    G->delta = delta;
    destruir_hash(hash);

    return ((lineas >= G->m) ? 0 : 1);
}
