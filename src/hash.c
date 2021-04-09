#include "hash.h"
#include <assert.h>
#include "../RomaVictor.h"
#include <math.h>
 
u32 hash_key(u32 vertice, u32 tam_hash)
{
  return ((vertice % tam_hash));
}

Hash_table *crear_tabla(u32 nvertices)
{
    Hash_table *hash = calloc(1, sizeof(struct Hash_table));
    hash->num_datos = nvertices;
    hash->tabla = (Element_t**)calloc(nvertices, sizeof(struct Element_t*));
    
    // for (u32 i = 0; i < nvertices; i++) {
    //   hash->tabla[i] = NULL;
    // }
    
    return hash;
}

void agregar_vertice(Vert *v, u32 posicion, Hash_table *hash)
{
  if (hash->tabla[posicion] == NULL) {
    hash->tabla[posicion] = (Element_t*)calloc(1, sizeof(struct Element_t));
    hash->tabla[posicion]->vertices = (Vert**)calloc(1, sizeof(struct Vert*));
    hash->tabla[posicion]->vertices[0] = v;
    hash->tabla[posicion]->tam = 1;
  } else {
      hash->tabla[posicion]->vertices = realloc(hash->tabla[posicion]->vertices, ((hash->tabla[posicion]->tam + 1) * sizeof(struct Vert)));
      hash->tabla[posicion]->vertices[hash->tabla[posicion]->tam] = v;
      hash->tabla[posicion]->tam++;
  }
}

Vert *buscar_vertice_en_hash(u32 key, u32 nombre, Hash_table *hash)
{
  if(hash->tabla[key] == NULL){
    return NULL;
  }else {
    for (u32 i = 0; i < hash->tabla[key]->tam; i++)
    {
      if(hash->tabla[key]->vertices[i]->nombre == nombre) {
        return hash->tabla[key]->vertices[i];
      }
    }
    return NULL;
  }
}

void destruir_hash(Hash_table *hash)
{
  printf("\nSe rompe\n");
  for (u32 i = 0; i < hash->num_datos; i++) {
    printf("\nSe rompe %u\n", i);
    if(hash->tabla[i] != NULL) {
      free(hash->tabla[i]->vertices);
      free(hash->tabla[i]);
    }
  }
  free(hash->tabla);
  free(hash);
}