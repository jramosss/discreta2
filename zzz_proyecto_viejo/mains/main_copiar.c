#include <stdio.h>
#include <time.h>
#include "veinteveinte.h"

static void display_all (Grafo G){
    printf("\n\nNombres: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%u,",Nombre(i,G));
    }
    printf("]\n");
    /*
    for(u32 i = 0; i < G->nvertices; i++){
        printf("\nArreglo de vecinos de %u [",i);
        for(u32 j = 0; j < G->vertices[i]->grado; j++){
            printf("%u,",NombreVecino(j,i,G));
        }
        printf("]\n");
    }   
    printf("]\n");
    printf("\nColores: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%u,",Color(i,G));
    }
    printf("]\n");
    printf("\nGrados: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%u,",Grado(i,G));
    }
    printf("]\n");*/
}

static char es_coloreo_propio(Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        for(u32 j = 0; j < Grado(i,G); j++){
            if(ColorVecino(j,i,G) == Color(i,G)){
                return 0;
            }
        }
    }
    return 1;
}

int main (void){
    clock_t start_t,end_t;
    double total_t = 0;
    start_t = clock();
    Grafo C = ConstruccionDelGrafo();
    printf("\nGRAFO INICIAL C\n");
    display_all(C);
    Grafo G = CopiarGrafo(C);
    printf("\nGRAFO INICIAL G\n");
    display_all(C);
    u32 vertice = 0;
    u32 vecino = 1;
    printf("\n====================Datos del grafo:====================\n");

    printf("Numero de vertices : %d \n",NumeroDeVertices(G));
    printf("Numero de lados : %d \n",NumeroDeLados(G));
    printf("Delta del grafo : %d\n",Delta(G));
    printf("Nombre de la raiz : %d \n",Nombre(vertice,G));
    printf("Color de la raiz : %d \n",Color(vertice,G));
    printf("Grado de la raiz : %d \n",Grado(vertice,G));
    printf("Nombre del vecino %d : %d \n",vecino,NombreVecino(vecino,vertice,G));
    printf("Color del vecino %d : %d \n",vecino,ColorVecino(vecino,vertice,G));
    printf("Grado del vecino %d : %d \n",vecino,OrdenVecino(vecino,vertice,G));


    printf("\n\n\n====================Estado Inicial(Con Greedy)====================\n\n\n");

    display_all(G);
    
    printf("\n\n\n====================BIPARTITO====================\n\n\n");

    char bip = Bipartito(G);
    printf(bip == '1' ? "El grafo es bipartito\n":"El grafo no es bipartito\n");

    printf("\n\n\n====================SWITCHCOLORES (0,'1')====================\n\n\n");

    char sw = SwitchColores(G,0,1);
    printf(sw == '1' ? "ERROR SwitchColores\n" : "BIEN: SwitchColores\n");
    display_all(G);

    printf("\n\n\n====================GREEDY====================\n\n\n");

    u32 gri = Greedy(G);
    printf("Greedy coloreo con %d colores\n",gri);
    display_all(G);
    printf(es_coloreo_propio(G) ? "El coloreo es propio\n":"El coloreo no es propio\n");

    printf("\n\n\n====================Funciones de ordenacion====================\n\n\n");
    printf("Estado Inicial\n");
    display_all(G);

    printf("\n\n\n====================ChicoGrandeBC====================\n\n\n");

    char cg = ChicoGrandeBC(G);
    printf(cg == '1'? "ERROR: ChicoGrande\n":"BIEN:ChicoGrande\n");
    printf(es_coloreo_propio(G) ? "El coloreo es propio\n":"El coloreo no es propio\n");
    display_all(G);

    printf("\n\n\n====================WELSHPOWEL====================\n\n\n");

    printf("Greedy antes de welsh\n");
    Greedy(G);
    char wp = WelshPowell(G);
    printf(wp == '1' ? "ERROR: WelshPowel\n":"BIEN:WelshPowel\n");
    Greedy(G);
    printf("Greedy despues de welsh\n");
    printf(es_coloreo_propio(G) ? "El coloreo es propio\n":"El coloreo no es propio\n");
    display_all(G);

    printf("\n\n\n====================BIPARTITO DESPUES DE WELSH====================\n\n\n");
    char bip2 = Bipartito(G);
    printf(bip2 == '1' ? "El grafo es bipartito\n":"El grafo no es bipartito\n");

    printf("\n\n\n====================ALEATORIZARVERTICES====================\n\n\n");
    u32 R = 1;
    printf("AleatorizarVertices con %u\n",R);
    char alv = AleatorizarVertices(G,R);
    display_all(G);
    printf(alv == '1' ? "ERROR: AleatorizarVertices\n":"BIEN:AleatorizarVertices\n");

    R++;
    printf("AleatorizarVertices con %u\n",R);
    alv = AleatorizarVertices(G,R);
    printf(alv == '1'? "ERROR: AleatorizarVertices\n":"BIEN:AleatorizarVertices\n");
    display_all(G);
    R++;

    printf("AleatorizarVertices con %u\n",R);
    alv = AleatorizarVertices(G,R);
    printf(alv == '1'? "ERROR: AleatorizarVertices\n":"BIEN:AleatorizarVertices\n");
    display_all(G);
    R++;

    printf("AleatorizarVertices con %u\n",R);
    alv = AleatorizarVertices(G,R);
    printf(alv == '1'? "ERROR: AleatorizarVertices\n":"BIEN:AleatorizarVertices\n");
    display_all(G);

    printf("\n\n\n====================NUMCCS====================\n\n\n");

    u32 cgs = NumCCs(G);
    printf("Numero de componentes conexas del grafo: %u\n",cgs);
    DestruccionDelGrafo(G);
    DestruccionDelGrafo(C);
    G = NULL;
    C = NULL;
    
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nEl programa tardo %f segundos en ejecutarse \n",total_t);

    fclose(stdin);
}