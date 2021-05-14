#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX, INT_MIN
#include <time.h>
#include "../RomaVictor.h"
#include "../src/utils.h"

void test_time (Grafo G,int times) {
    while (times--)
        AleatorizarVertices(G,6);    
}

void try_diff_seeds_aux (Grafo G,u32 times) {
    u32 R = 1;
    while(times--) {
        AleatorizarVertices(G,R);
        print_arr_vertices(G);
        printf("[");
        for (u32 j = 0; j < NumeroDeVertices(G); j++)
            printf(j == NumeroDeVertices(G)-1 ? "%u" : "%u,",G->orden_natural[j]->nombre);
        printf("]");
        R++;
    }
}

void try_diff_seeds (Grafo G,u32 times) {
    u32 R = 1;
    while(times--) {
        AleatorizarVertices(G,R);
        printf("Con R = %u: \n",R);
        R++;
        print_arr_vertices(G);
    }
}

int main (int argc, char* argv[]) {
    char* p;
    long times = 1;
    errno = 0;

    if (argc == 2){
        times = strtol(argv[1], &p, 10);
        if (errno != 0 || *p != '\0' || times > INT_MAX || times < INT_MIN) {
            printf("Error en la conversion a entero\n");
            return 1;
        }
    }

    Grafo G = ConstruccionDelGrafo();

    clock_t start = clock();
    test_time(G,(int)times);
    clock_t end = clock();
    printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC);

    //print_arr_vertices(G);

    DestruccionDelGrafo(G);

    return 0;
}
