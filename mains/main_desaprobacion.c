#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/utils.h"
#include "src/parser.h"

static void display_all (Grafo G){
    /*printf("\n\nNombres: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%u,",Nombre(i,G));
    }
    printf("]\n");
    printf("\nColores: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%u,",Color(i,G));
    }
    printf("]\n");
    */
    printf("\nGrados: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%u,",Grado(i,G));
    }
    printf("]\n");
}

static bool es_coloreo_propio(Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); i++)
        for(u32 j = 0; j < Grado(i,G); j++)
            if(ColorVecino(j,i,G) == Color(i,G))
                return false;

    return true;
}

int main(void){
    clock_t start_t, end_t; 
    double total_t;
    start_t = clock();
    printf("Construimos el Grafo\n");
    Grafo G = ConstruccionDelGrafo();
    
    u32 vertice = 0;
    u32 vecino = 1;
    printf("\n====================Datos del grafo:====================\n");

    printf("Numero de vertices : %d \n",            NumeroDeVertices(G));
    printf("Numero de lados : %d \n",               NumeroDeLados(G));
    printf("Delta del grafo : %d\n",                Delta(G));
    printf("Nombre de la raiz : %d \n",             Nombre(vertice,G));
    printf("Color de la raiz : %d \n",              Color(vertice,G));
    printf("Grado de la raiz : %d \n",              Grado(vertice,G));
    printf("Nombre del vecino %d : %d \n",          vecino,NombreVecino(vecino,vertice,G));
    printf("Color del vecino %d : %d \n",           vecino,ColorVecino(vecino,vertice,G));
    printf("Grado del vecino %d : %d \n",           vecino,OrdenVecino(vecino,vertice,G));
    printf("Numero de componentes conexas: %u\n",   NumCCs(G));

    bool muy_grande = NumeroDeVertices(G) > 10;

    if (!muy_grande) {
        section("Estado Inicial(Con Greedy)");
        display_all(G);
    }
    
    section("BIPARTITO");

    char bip = Bipartito(G);
    check_bipartito(bip);

    section("SWITCHCOLORES (0,'1')");

    char sw = SwitchColores(G,0,1);
    check_sc(sw);
    char bip4 = Bipartito(G);
    check_bipartito(bip4);
    if (!muy_grande) display_all(G);

    section("GREEDY");

    const u32 gri = Greedy(G);
    printf("Greedy coloreo con %d colores\n",gri);
    if (!muy_grande) display_all(G);
    const char bip5 = Bipartito(G);
    check_bipartito(bip5);
    check_coloreo_propio(es_coloreo_propio(G));
    section("Funciones de ordenacion");
    section("Estado Inicial\n");
    if (!muy_grande) display_all(G);

    section("ChicoGrandeBC");

    const char cg = ChicoGrandeBC(G);
    check_chicogrande(cg);
    printf(es_coloreo_propio(G) ? "El coloreo es propio\n":"El coloreo no es propio\n");
    char bip7 = Bipartito(G);
    check_bipartito(bip7);
    if (!muy_grande) display_all(G);

    section("WELSHPOWELL");

    printf("Greedy antes de welsh\n");
    Greedy(G);
    const char wp = WelshPowell(G);
    check_wp(wp);
    Greedy(G);
    printf("Greedy despues de welsh\n");
    check_coloreo_propio(es_coloreo_propio(G));
    const char bip3 = Bipartito(G);
    check_bipartito(bip3);
    if (!muy_grande) display_all(G);

    section("BIPARTITO DESPUES DE WELSH");
    const char bip22 = Bipartito(G);
    check_bipartito(bip22);
    //Aca hacia bipartito de vuelta pero como no se por que lo haciamos lo saque

    section("ALEATORIZARVERTICES");
    u32 R = 1;
    printf("AleatorizarVertices con %u\n",R);
    char alv = AleatorizarVertices(G,R);
    if (!muy_grande) display_all(G);
    check_alv(alv);

    R++;
    printf("AleatorizarVertices con %u\n",R);
    alv = AleatorizarVertices(G,R);
    check_alv(alv);
    if (!muy_grande) display_all(G);
    R++;

    printf("AleatorizarVertices con %u\n",R);
    alv = AleatorizarVertices(G,R);
    check_alv(alv);
    if (!muy_grande) display_all(G);
    R++;

    printf("AleatorizarVertices con %u\n",R);
    alv = AleatorizarVertices(G,R);
    check_alv(alv);
    if (!muy_grande) display_all(G);
    char bip99 = Bipartito(G);
    check_bipartito(bip99);

    section("NUMCCS");

    const u32 cgs = NumCCs(G);
    printf("Numero de componentes conexas del grafo: %u\n",cgs);

    DestruccionDelGrafo(G);
    G = NULL;
    
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nEl programa tardo %f segundos en ejecutarse \n",total_t);


    fclose(stdin);
}