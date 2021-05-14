#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX, INT_MIN
#include <time.h>
#include "../RomaVictor.h"
#include "../src/utils.h"

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

    //Test time
    u32 seed = 4;

    bool first = true;
    bool snd   = false;
    const u32 N = NumeroDeVertices(G);
    u32* fst_result = malloc(N*sizeof(u32));

    while (times--){
        for (u32 i = 0; i < 2; i++){
            AleatorizarVertices(G,seed);
            if (first) {
                for(u32 loop = 0; loop < N; loop++)
                    fst_result[loop] = G->vertices[loop]->nombre;
                first = false;
                snd = true;
            }
            if (snd)
                snd = false;
        }
        print_arr(fst_result,N);
        printf("[");
        for (u32 i = 0; i < N; i++) 
            printf(i == N-1 ? "%u" : "%u,",G->vertices[i]->nombre);
        first = true;
        seed++;
    }

    free(fst_result);

    DestruccionDelGrafo(G);

    return 0;
}
