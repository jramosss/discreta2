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

    const u32 R = 10;

    AleatorizarVertices(G,R);

    print_arr_vertices(G);

    DestruccionDelGrafo(G);

    return 0;
}
