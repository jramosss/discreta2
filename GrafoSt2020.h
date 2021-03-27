typedef unsigned int u32;

typedef struct Vert {
    u32         nombre;
    u32         grado;
    u32         color;
    u32         index;
    struct Vert **vecinos;
} Vert;

typedef struct GrafoSt {
    u32     n;                      // Numero de vertices
    u32     m;                      // Numero de lados
    u32     delta;                  // Mayor numero de vecinos de un vertice, 
                                    //? podriamos calcularlo mientras se hace el parseo 
    Vert    *raiz;                  
    Vert    **vertices;             // Arreglo de vertices que representa el orden de cada vertice. 
                                    // Donde a index se le va a asignar su lugar en el arreglo.
    Vert    **orden_numerico;       // Yo opino que tengamos el orden numerico guardado en la struct                                    
                                    // Y que este sea simplemente hacer un sort cuando se cree el 
                                    // arreglo de vertices
} GrafoSt;