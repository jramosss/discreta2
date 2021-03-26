typedef unsigned int u32;

typedef struct Tuple {
    u32         vx;
    u32         vy;
} Tuple;

typedef struct Vert {
    u32         nombre;
    u32         grado;
    u32         color;
    u32         index;
    u32         visited;            //Necesitamos este campo para greedy
    struct Vert **vecinos;          //TODO borrar estos 3 campos
    struct Vert *vert_iz;
    struct Vert *vert_de;
} Vert;

typedef struct GrafoSt {
    u32     nvertices;
    u32     nlados;
    u32     delta;
    Vert    *raiz;
    Tuple   *parseo;                // Arreglo de lados
    Vert    **orden;                //TODO Refactorizar a Orden_nat, Arregle con vertices en orden natural
    Vert    **vertices;             // Arreglo de vertices que representa el orden de cada vertice. 
                                    // Donde a index se le va a asignar su lugar en el arreglo.
} GrafoSt;