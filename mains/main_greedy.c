#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX, INT_MIN
#include <time.h>
#include "../RomaVictor.h"

int main(int argc,char* argv[]) {
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

    for (u32 i = 0; i < NumeroDeVertices(G); i++) 
        FijarOrden(i,G,i);  

    clock_t start = clock();
    
    u32 colores = 0;

    for (long i = 0; i < times; i++)
        colores = Greedy(G);

    clock_t end = clock();
    double total = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%u %f\n", colores,total);
    DestruccionDelGrafo(G);
}