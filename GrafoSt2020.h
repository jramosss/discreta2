typedef unsigned int u32;

typedef struct Vert {
    u32         nombre;
    u32         grado;
    u32         color;
    u32         index;
    struct Vert **vecinos;
} Vert;

typedef struct GrafoSt {
    u32     n;                      // Numero de vertices del grafo 
    u32     m;                      // Numero de lados del grafo
    u32     delta;                  // Mayor numero de vecinos
    Vert    *raiz;
    Vert    **orden_numerico;       // Arreglo de vertices en orden numerico [1,2,...,n]
    Vert    **vertices;             // Arreglo de vertices con el orden en el que fue parseado el grafo
} GrafoSt;