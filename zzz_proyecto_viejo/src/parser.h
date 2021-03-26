#include <stdbool.h>
#include "../veinteveinte.h"
#define MAXCHAR 80


/* --------- Initialize the structs --------- */
Vert *vert_create(u32 name, u32 mlados);

/* --------- Extract info from file --------- */
Tuple *array_of_tuples (FILE *filename, Grafo graph);

/* --------- fill the graph strcut --------- */
void graph_fill(Grafo graph);               // Ya no se necesita Tuple *array como argumento, ya que se encuentra dentro de la estructura Grafo.
void fill_vecinos(Grafo graph);             // Ya no se necesita Tuple *array como argumento, ya que se encuentra dentro de la estructura Grafo.
Vert *find_vert_by_index(u32 i, Grafo graph);
Vert *find_vert_by_name(u32 name, Vert *raiz);
void orden_fill(Grafo graph, u32 i, Vert *v);        // Arreglo que contiene a los vertices en el orden inicial en que se crea el grafo.
