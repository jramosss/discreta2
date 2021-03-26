typedef unsigned int u32;

typedef struct Vert {
    u32         nombre;
    u32         grado;
    u32         color;
    u32         index;
    struct Vert **vecinos;          //TODO borrar estos 3 campos
} Vert;

typedef struct GrafoSt {
    u32     nvertices;
    u32     nlados;
    u32     delta;
    Vert    *raiz;
    Vert    **orden;                //TODO Refactorizar a Orden_nat, Arregle con vertices en orden natural
    Vert    **vertices;             // Arreglo de vertices que representa el orden de cada vertice. 
                                    // Donde a index se le va a asignar su lugar en el arreglo.
} GrafoSt;