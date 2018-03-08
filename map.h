#ifndef _MAP_
#define _MAP_

#include "point.h"
#include "types.h"

#define MAX_MAP 2048

typedef struct _Map Map;


/* Movimientos posibles en un mapa*/
typedef enum {
  RIGHT=0,
  UP=1,
  LEFT=2,
  DOWN=3,
  STAY=4
} Move;


/* Inicializa un mapa, reservando memoria y devolviendo el mapa
inicializado si lo ha hecho correctamente o NULL si no */
Map* map_ini();


/* Libera la memoria dinámica reservada para un mapa */
void map_free(Map* );


/* Devuelve el número de filas de un mapa dado, o -1 si seproduce algún error */
int map_getNrows(const Map* );


/* Devuelve el número de columnas de un mapadado, o -1 si se produce algún error */
int map_getNcols(const Map* );


/* Devuelve el punto de entrada en un mapadado, o NULL si se produce algún
 error o no existe un punto de ese tipo */
Point * map_getInput(const Map* );


/* Devuelve el punto de salida en un mapadado, o NULL si se produce algún
error o no existe un punto de ese tipo */
Point * map_getOutput(const Map* );


/* Devuelve el punto resultante al realizar un movimiento en un mapa a
 partir de un punto inicial, o NULL si se produce algún error */
Point * map_getNeighborPoint(const Map* , const Point *, const Move mov);


/* Indica el tamaño de un mapa, devuelve NULL si se produce algún error */
Status map_setSize(Map* , int nrow, int ncol);


/* Añade un punto a un mapa dadoreservando nueva memoria (de ahí que el
argumento sea declarado como const), o modifica el punto si ya se encuentra.
Debe comprobar si el punto es de tipo Output o Input para guardarlo como
corresponda.Devuelve OK si todo ha ido correctamente (se ha podido
incluir/actualizar el punto). */
Status map_setPoint(Map* , const Point* );


/* Imprime en un fichero dado los datos de un mapa. Además,devolverá el número
de caracteres que se han escrito con éxito (mirar documentación de fprintf) */
int map_print(FILE *, const Map* );


Status map_read(FILE *pf, Map *pl);

#endif
