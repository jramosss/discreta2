#include <stdio.h>
#include "veinteveinte.h"

int main(void) {
    Grafo G = ConstruccionDelGrafo();
    if (Bipartito(G) == '1'){
        AleatorizarVertices(G, 1245);
        ChicoGrandeBC(G);
        if (WelshPowell(G) == '0'){            
            printf("%c", Bipartito(G));
        }
    } else {
        AleatorizarVertices(G, 282);
        RevierteBC(G);
        if (WelshPowell(G) == '0'){
            printf("%c", Bipartito(G));
        }
    }
    DestruccionDelGrafo(G);
    return 0;
}