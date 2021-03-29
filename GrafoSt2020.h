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
    Vert    **orden_natural;        // Arreglo de vertices donde cada index se corresponde con el orden en el que fueron parseados
    Vert    **vertices;             // Arreglo de vertices con el orden en el que fue parseado el grafo
} GrafoSt;