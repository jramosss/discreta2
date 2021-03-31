#include "hash.h"
#include <assert.h>
#include "../veinteveinte.h"

u32 hash_key(u32 vertice, u32 tamaño_hash)
{
  return (vertice % tamaño_hash);
}

Hash_table *crear_tabla(u32 nvertices)
{
    assert(nvertices > 0);
    Hash_table *hash = calloc(1, sizeof(struct Hash_table));
    hash->num_datos = nvertices;
    hash->tabla = calloc(nvertices, sizeof(struct Element_t));
    
    for (u32 i = 0; i < nvertices; i++) {
      hash->tabla[i] = NULL;
    }
    
    return hash;
}

void agregar_vertice(Vert *v, Element_t *i_lugar)
{
  if (i_lugar == NULL) {
    i_lugar = calloc(1, sizeof(struct Element_t));
    i_lugar->vertices = calloc(1, sizeof(struct Vert));
    i_lugar->vertices[0] = v;
    i_lugar->usados = 1;
  } else {
      i_lugar->usados++;
      i_lugar->vertices = realloc(i_lugar->vertices, (i_lugar->usados * sizeof(struct Vert)));
      i_lugar->vertices[i_lugar->usados] = v;
  }
}

u32 buscar_vertice_en_hash(u32 key, u32 nombre, Hash_table *hash)
{
  if(hash->tabla[key] == NULL){
    return 0;
  }else {
    for (u32 i = 0; i < hash->tabla[key]->usados; i++)
    {
      if(hash->tabla[key]->vertices[i]->nombre == nombre) {
        return 1;
      }
    }
  }
  return 0;
}