#include "../veinteveinte.h"

typedef struct Element_t
{
  Vert **vertices;
  u32 tam;
} Element_t;

typedef struct Hash_table
{
  Element_t **tabla;
  u32 num_datos;
} Hash_table;

u32 hash_key(u32 vertice, u32 tam_hash);

/** Crea la tabla hash con n posiciones 
 * @param nvertices tamaño de la tabla a crear
 * @return puntero a la tabla
*/
Hash_table *crear_tabla(u32 nvertices);

/** Busca al vertice en la tabla
 * @param key posicion del vertice en la tabla
 * @param nombre nombre del vertice a buscar
 * @param hash tabla en la que se busca el vertice
 * @return 1 si está, 0 caso contrario.
*/
u32 buscar_vertice_en_hash(u32 key, u32 nombre, Hash_table *hash);


/** Agrega un vertice en la tabla hash, si se produce una colision es decir ya hay un vertice en esa 
  posicion, se lo agrega a en la siguiente posicion del arreglo vertices disponible.
  * @param v vertice a agregar.
  * @param posicion posicion en la tabla hash.
  * @param hash tabla hash donde se agrega el vertice
*/
void agregar_vertice(Vert *v, u32 posicion, Hash_table *hash);