#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "veinteveinte.h"

static void display_all (Grafo G){/*
    printf("\nNombres: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%d,",Nombre(i,G));
    }
    printf("]\n");
    printf("\nColores: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%d,",Color(i,G));
    }
    printf("]\n");
    printf("\nGrados: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%d,",Grado(i,G));
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

static void check_welsh(Grafo G){
    bool b = true;
    for(u32 i = 0; i < NumeroDeVertices(G)-1; i++){
        if(Grado(i,G) < Grado(i+1,G)){
            b = false;
        }
    }
    printf(b ? "BIEN2: WelshPowel\n" : "ERROR2: WelshPowel\n");
}

static void check_cg(Grafo G){
    bool b = true;
    for(u32 i = 0; i < NumeroDeVertices(G)-1; i++){ //Check ChicoGrandeBC
        if(Color(i,G) > Color(i+1,G)){
            b = false;   
        }
        
    }
    printf(b ? "BIEN2: ChicoGrande\n" : "ERROR2: ChicoGrande");
}

int main(void){
    clock_t start_t, end_t; 
    double total_t;
    start_t = clock();
    Grafo G = ConstruccionDelGrafo();  // Ahora en la construccion tambien hacemos el llenado del grafo y de vecinos.
    
    printf("\n\n\n====================Datos del grafo====================\n\n\n");

    u32 vertice = 0;
    u32 vecino = 1;

    printf("Numero de vertices : %d \n",NumeroDeVertices(G));
    printf("Numero de lados : %d \n",NumeroDeLados(G));
    printf("Delta del grafo : %d\n",Delta(G));
    printf("Nombre de la raiz : %d \n",Nombre(vertice,G));
    printf("Color de la raiz : %d \n",Color(vertice,G));
    printf("Grado de la raiz : %d \n",Grado(vertice,G));
    printf("Nombre del vecino %d : %d \n",vecino,NombreVecino(vecino,vertice,G));
    printf("Color del vecino %d : %d \n",vecino,ColorVecino(vecino,vertice,G));
    printf("Grado del vecino %d : %d \n",vecino,OrdenVecino(vecino,vertice,G));

    printf("\n\n====================Funciones de coloreo====================\n\n");


    char bip = Bipartito(G);
    printf(bip ? "El grafo es bipartito\n":"El grafo no es bipartito\n");
    char sw = SwitchColores(G,0,1);
    printf(sw ? "ERROR SwitchColores\n" : "BIEN: SwitchColores\n");
    //display_all(G);
    u32 gri = Greedy(G);
    printf("Greedy coloreo con %d colores\n",gri);
    printf(es_coloreo_propio(G) ? "El coloreo es propio\n":"El coloreo no es propio\n");
    //display_all(G);
    

    printf("\n\n====================Funciones de ordenacion====================\n\n");
    

    printf("Greedy antes de ChicoGrande\n");  //Corro un greedy antes de cada funcion para corroborar que no rompa nada
    Greedy(G);
    printf(es_coloreo_propio(G) ? "El coloreo es propio\n":"El coloreo no es propio\n");
    display_all(G);
    char cg = ChicoGrandeBC(G);
    printf(cg ? "ERROR: ChicoGrande\n":"BIEN:ChicoGrande\n");
    printf(es_coloreo_propio(G) ? "El coloreo es propio\n":"El coloreo no es propio\n");
    check_cg(G);
    
    printf("Greedy antes de welsh\n");
    Greedy(G);
    char wp = WelshPowell(G);
    printf(wp ? "ERROR: WelshPowel\n":"BIEN:WelshPowel\n");
    check_welsh(G);

    Greedy(G);
    printf("Greedy despues de welsh\n");
    printf(es_coloreo_propio(G) ? "El coloreo es propio\n":"El coloreo no es propio\n");
    //display_all(G);
    u32 R = 0;
    printf("AleatorizarVertices con %d\n",R);
    char alv = AleatorizarVertices(G,R);
    //display_all(G);
    printf(alv ? "ERROR: AleatorizarVertices\n":"BIEN:AleatorizarVertices\n");
    R++;/*
    printf("AleatorizarVertices con %d\n",R);
    alv = AleatorizarVertices(G,R);
    printf(alv ? "ERROR: AleatorizarVertices\n":"BIEN:AleatorizarVertices\n");
    //display_all(G);
    R++;
    printf("AleatorizarVertices con %d\n",R);
    alv = AleatorizarVertices(G,R);
    printf(alv ? "ERROR: AleatorizarVertices\n":"BIEN:AleatorizarVertices\n");
    //display_all(G);
    R++;
    printf("AleatorizarVertices con %d\n",R);
    alv = AleatorizarVertices(G,R);
    printf(alv ? "ERROR: AleatorizarVertices\n":"BIEN:AleatorizarVertices\n");
    //display_all(G);*/
    u32 cgs = NumCCs(G);
    printf("Numero de componentes conexas del grafo: %d\n",cgs);
    DestruccionDelGrafo(G);
    G = NULL;
    
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nEl programa tardo %f segundos en ejecutarse \n",total_t);


    fclose(stdin);
}