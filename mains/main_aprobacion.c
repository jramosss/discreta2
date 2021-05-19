#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX, INT_MIN
#include <stdio.h>
#include <time.h>
#include "../RomaVictor.h"

int main (int argc,char* argv[]) {
    long times = 1;
    char* p;
    errno = 0;
    if (argc == 2) {
        times = strtol(argv[1], &p, 10);
        if (errno != 0 || *p != '\0' || times > INT_MAX || times < INT_MIN) {
            printf("Error en la conversion a entero\n");
            return 1;
        }
    }
    
    Grafo G = ConstruccionDelGrafo();

    clock_t start = clock();
    for (int i = 0; i < times; i++) {
        Greedy(G);
        AleatorizarVertices(G,4);
    }
    clock_t end = clock();
    double total = (double)(end-start)/CLOCKS_PER_SEC;

    printf("%f\n",total);

    DestruccionDelGrafo(G);

    return 0;
}
