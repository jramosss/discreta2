#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "../src/utils.h"
#include "../veinteveinte.h"

const double MAX_TIME = 60*15;

static bool ordena_bien (Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G)-1; i++)
        if(Grado(i,G) < Grado(i+1,G))
            return false;
    return true;
}

static bool coloreo_propio (Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); i++)
        for(u32 j = 0; j < Grado(i,G) ; j++)
            if(Color(i,G) == ColorVecino(j,i,G))
                return false;
    return true;
}

static void display_all (Grafo G){/*
    printf("\n\nNombres: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%u,",Nombre(i,G));
    }
    printf("]\n");
    printf("\nGrados: [");
    for(u32 i = 0; i < G->nvertices; i++){
        printf("%u,",Grado(i,G));
    }
    printf("]\n");*/
    
    printf("\nColores: [");
    for(u32 i = 0; i < G->nvertices; i++)
        printf("%u,",Color(i,G));
        
    printf("]\n");
}

int main (void){

    clock_t start_t, end_t; 
    double total_t;
    start_t = clock();

    u32 bipartito = 0;
    u32 coloreoprop = 0;
    Grafo G = ConstruccionDelGrafo();

    blank(1);

    check_cond(coloreo_propio(G),"El coloreo es propio", "El coloreo no es propio");
    
    display_all(G);

    printf("\n====================BIPARTITO====================\n");

        char bip = Bipartito(G);
        check_cond(bip,"El grafo es bipartito","El grafo np es bipartito");
        check_cond(coloreo_propio(G), "El coloreo es propio", "El coloreo no es propio");
        if(bip) bipartito++;
        if(coloreo_propio(G)) coloreoprop++;
        display_all(G);

    printf("\n====================WELSHPOWEL====================\n");

        printf("Greedy antes de welsh\n");
        Greedy(G);
        char wp = WelshPowell(G);
        check_cond(!wp,"BIEN:WelshPowel","ERROR: WelshPowel");

        //display_all(G);
        check_cond(ordena_bien(G),"ORDENA BIEN","ORDENA MAL");

        u32 greedy_after_wp = Greedy(G);
        check_cond((char)greedy_after_wp,"Greedy despues de welsh","Greedy despues de welsh");
    
    printf("\n====================BIPARTITO DESPUES DE WELSH====================\n");
        char bip2 = Bipartito(G);
        check_cond(bip2,"El grafo es bipartito","El grafo no es bipartito");

        check_cond(coloreo_propio(G),"El coloreo es propio","El coloreo no es propio");

        if(bip2) bipartito++;
        if(coloreo_propio(G)) coloreoprop++;

        display_all(G);
        char av;
        char bip3;
        for (u32 i = 0; i < 5; i++){
            printf("\n====================ALEATORIZARVERTICES CON %d====================\n",i);
            av = AleatorizarVertices(G,i);
            check_cond(!av,"BIEN: AleatorizarVertices","ERROR: Aleatorizar Vertices");

            printf("\n====================BIPARTITO DESPUES DE ALEATORIZARV %d====================\n",i);
            bip3 = Bipartito(G);
            check_cond(bip3,"El grafo es bipartito","El grafo no es bipartito");

            check_cond(coloreo_propio(G),"El coloreo es propio","El coloreo no es propio");

            if(bip3) bipartito++;

            if(coloreo_propio(G)) coloreoprop++;
        }

    printf("\n====================CHICOGRANDE====================\n");
        char cg = ChicoGrandeBC(G);
        check_cond(!cg,"BIEN: ChicoGrande","ERROR: ChicoGrande");

    printf("\n====================BIPARTITO DESPUES DE CHICOGRANDE====================\n");
        char bip4 = Bipartito(G);
        check_cond(bip4,"El grafo es bipartito","El grafo no es bipartito");

        check_cond(coloreo_propio(G), "El coloreo es propio", "El coloreo no es propio");
        display_all(G);
        if(bip4) bipartito++;
        if(coloreo_propio(G)) coloreoprop++;

    printf("\n====================REVIERTEBC====================\n");
        char rbc = RevierteBC(G);
        check_cond(!rbc, "BIEN:RevierteBC","ERROR: RevierteBC");

    printf("\n====================BIPARTITO DESPUES DE REVIERTEBC====================\n");
        char bip5 = Bipartito(G);
        check_cond(bip5, "El grafo es bipartito","El grafo no es bipartito");
        check_cond(coloreo_propio(G), "El coloreo es propio" , "El coloreo no es propio");
        display_all(G);
        if(bip5) bipartito++;
        if(coloreo_propio(G)) coloreoprop++;

    printf("\n====================REVIERTEBC====================\n");
        char sw = SwitchColores(G,0,1);
        check_cond(!sw , "BIEN:RevierteBC","ERROR: RevierteBC");

    printf("\n====================BIPARTITO DESPUES DE REVIERTEBC====================\n");
    
        char bip6 = Bipartito(G);
        check_cond(bip6 , "El grafo es bipartito","El grafo no es bipartito");
        check_cond(coloreo_propio(G), "El coloreo es propio" , "El coloreo no es propio");
        display_all(G);
        if(bip6) bipartito++;
        if(coloreo_propio(G)) coloreoprop++;


    printf("Numero de componentes conexas: %u\n",NumCCs(G));
    printf("BIPARTITOS (%d/9)\n",bipartito);
    printf("COLOREOS PROPIOS (%d/9)\n",coloreoprop-1);

    DestruccionDelGrafo(G);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nEl programa tardo %f segundos en ejecutarse\n",total_t);
}