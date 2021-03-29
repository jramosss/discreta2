#ifndef __vv_H
#define __vv_H


#include <stdio.h>
#include <stdlib.h>



#include "GrafoSt2020.h"

//Grafo es un puntero a una estructura, la cual esta definida en el .h de arriba

typedef GrafoSt *Grafo;


//construcci'on/destrucci'on

Grafo ConstruccionDelGrafo(void);

void DestruccionDelGrafo(Grafo G);

Grafo CopiarGrafo(Grafo G);

//funciones para extraer datos del grafo. u32 esta definida en el .h de arriba

u32 NumeroDeVertices(Grafo G);
u32 NumeroDeLados(Grafo G);
u32 Delta(Grafo G);


//funciones de infoextract de vertices 
//valor de retorno (2 a la 32)-1 para reportar errores.
//salvo para las de "Nombre" que no tienen forma de reportar errores.
//las otras no hay problema pues es imposible que (2 a la 32)-1 sea un color o un grado.
u32 Nombre(u32 i,Grafo G);
u32 Color(u32 i,Grafo G);
u32 Grado(u32 i,Grafo G);

//vecinos info
u32 ColorVecino(u32 j,u32 i,Grafo G);
u32 NombreVecino(u32 j,u32 i,Grafo G);
u32 OrdenVecino(u32 j,u32 i,Grafo G);


//Funciones para modificar datos de los v'ertices, char es para retornar error
//si se le pide algo fuera de rango o un alloc error.

//asigna color x al vertice i del orden interno

/**
 * @param x el color a asignar
 * @param idx el index del vertice
 * @param G el grafo 
 * @returns '0' si salio todo bien,'1' si algo salio mal
*/
char FijarColor(u32 x,u32 i,Grafo G);

/**
 * @param i El lugar a asignar
 * @param G El grafo 
 * @param N El index en el arreglo de orden natural 
 * @returns '0' si salio todo bien, '1' si algo salio mal
 * asigna en el lugar i del orden el vertice N-esimo del orden natural.
*/
char FijarOrden(u32 i,Grafo G,u32 N);


//orden Welsh Powell: por grados del mayor al menor
char WelshPowell(Grafo G);

//revierte los bloques de colores
char RevierteBC(Grafo G);

//ordena por cardinalidad de los bloques de colores, del mas chico al mas grande
char ChicoGrandeBC(Grafo G);

//pseudo-aleatoriza vertices usando semilla R.
char AleatorizarVertices(Grafo G,u32 R);

//intercambia esos colores
char SwitchColores(Grafo G,u32 i,u32 j);




char Bipartito(Grafo G);
u32 Greedy(Grafo G);



u32 NumCCs(Grafo G);



#endif