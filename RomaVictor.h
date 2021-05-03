#ifndef __vv_H
#define __vv_H


#include <stdio.h>
#include <stdlib.h>



#include "GrafoSt2021.h"

//Grafo es un puntero a una estructura, la cual esta definida en el .h de arriba

typedef GrafoSt *Grafo;


//--------------------Funciones de Construccion/Destruccion--------------------

Grafo ConstruccionDelGrafo(void);

/**
 * Esta funcion libera la memoria alocada para el grafo G incluyendo la memoria
 * alocada para los vertices de G.
 * @param Grafo G
 */
void DestruccionDelGrafo(Grafo G);

/**
 * Esta funcion crea una nueva instancia de un grafo G y copia todos sus 
 * atributos
 * @param Grafo G
 * @return Grafo Copy
 */
Grafo CopiarGrafo(Grafo G);

//--------------------Funciones para extraer datos del grafo.--------------------

u32 NumeroDeVertices(Grafo G);
u32 NumeroDeLados(Grafo G);
u32 Delta(Grafo G);


//--------------------Funciones de extraccion de info de los vertices --------------------

/**
 * Dado un index i y un grafo retorna el nombre de ese vertice
 * @param i index
 * @param G el grafo
 * @return Name
*/
u32 Nombre(u32 i,Grafo G);

/**
 * Dado un index i y un grafo retorna el color de ese vertice
 * @param i index
 * @param G el grafo
 * @return Color, 2^32-1 (error) en caso de error
*/
u32 Color(u32 i,Grafo G);

/**
 * Dado un index i y un grafo retorna el nombre de ese vertice
 * @param i index
 * @param G el grafo
 * @return Grado, 2^32-1 (error) en caso de error
*/
u32 Grado(u32 i,Grafo G);


//--------------------Info de los vecinos--------------------

/**
 * Retorna el color del vecino numero j del vertice numero i en el orden  guardado en ese momento en G 
 * @param j 
 * @param i
 * @param G
 * @returns Color, error (2^32-1) si i >= G->n ò j >= vert->grado
*/
u32 ColorVecino(u32 j,u32 i,Grafo G);

/**
 * Retorna el nombre del vecino numero j del vertice numero i en el orden guardado en ese momento en G 
 * @param j 
 * @param i
 * @param G
 * @returns Nombre, error (2^32-1) si i >= G->n ò j >= vert->grado
*/
u32 NombreVecino(u32 j,u32 i,Grafo G);

/**
 * Devuelve el orden del vecino numero j del vertice numero i en el orden guardado en ese momento en G 
 * @param j 
 * @param i
 * @param G
 * @returns Color, error (2^32-1) si i >= G->n ò j >= vert->grado
*/
u32 OrdenVecino(u32 j,u32 i,Grafo G);

/** 
 * Devuelve el peso del lado formado por el i-´esimo v´ertice de G en el orden interno con el j-´esimo vecino de ese v´ertice. 
 * @param j j-esimo vecino de i
 * @param i i-esimo vertice en orden interno
 * @param G grafo que contiene los vertices
*/
u32 PesoLadoConVecino(u32 j,u32 i,Grafo G);


//--------------------Funciones para modificar datos de los vertices--------------------


/**
 * Asigna el color x al vertice i del orden interno
 * @param x el color a asignar
 * @param idx el index del vertice
 * @param G el grafo 
 * @returns '0' si salio todo bien,'1' si algo salio mal
*/
char FijarColor(u32 x,u32 i,Grafo G);

/**
 * Asigna en el lugar i del orden el vertice N-esimo del orden natural.
 * @param i El lugar a asignar
 * @param G El grafo 
 * @param N El index en el arreglo de orden natural 
 * @returns '0' si salio todo bien, '1' si algo salio mal
*/
char FijarOrden(u32 i,Grafo G,u32 N);

/**
 * Hace que el lado formado por el i-´esimo v´ertice de G en el orden interno con el j-´esimo vecino de ese v´ertice tenga peso p.
 * @param j j-esimo vertice de i
 * @param i i-esimo vertice de G, orden interno 
 * @param p peso a asignar
 * @param G El grafo
*/
u32 FijarPesoLadoConVecino(u32 j,u32 i,u32 p,Grafo G);

/*
//orden Welsh Powell: por grados del mayor al menor
char WelshPowell(Grafo G);

//revierte los bloques de colores
char RevierteBC(Grafo G);

//ordena por cardinalidad de los bloques de colores, del mas chico al mas grande
char ChicoGrandeBC(Grafo G);
*/

/**
 * "Aleatoriza” el orden de los vertices de G, usando como semilla de aleatoridad el numero R
 * @param G El grafo
 * @param R la semilla
 * @returns '0' si todo anduvo bien, '1' si algo salio mal
*/
char AleatorizarVertices(Grafo G,u32 R);
/*
//intercambia esos colores
char SwitchColores(Grafo G,u32 i,u32 j);
*/

char Bipartito(Grafo G);

//u32 NumCCs(Grafo G);

/**
 * Corre Greedy en G comenzando con el color 0, utiliando el orden interno que 
 * debe estar guardado de alguna forma dentro de G.
 * @param Grafo G
 * @return u32 cantidad_colores
 */ 
u32 Greedy(Grafo G);



#endif