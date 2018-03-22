#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "point.h"
#include "map.h"


struct _Map
{
  int nRows;
  int nCols;
  Point* data [MAX_MAP];
  Point* input;
  Point* output;
};

/* Inicializa un mapa, reservando memoria y devolviendo el mapa
inicializado si lo ha hecho correctamente o NULL si no */
Map* map_ini()
{
  Map* newMap = NULL;

  /* Reserva memoria y comprueba si se ha reservado correctamente */
  newMap = (Map*) calloc(1, sizeof(Map));
  if (newMap == NULL)
    return NULL;

  return newMap;
}

/* Libera la memoria dinámica reservada para un mapa, y los puntos que contiene */
void map_free(Map* map)
{
  int i;

  if (!map)
    return;

  for (i=0; i<MAX_MAP; i++)
  {
    point_destroy(map->data[i]);
    map->data[i] = NULL;
  }

  free(map);
}


int map_getNrows(const Map* map)
{
  return map->nRows;
}


int map_getNcols(const Map* map)
{
  return map->nCols;
}


Point* map_getInput(const Map* map)
{
  return map->input;
}


Point* map_getOutput(const Map* map)
{
  return map->output;
}


/* Devuelve el punto resultante al realizar un movimiento en un mapa a
 partir de un punto inicial, o NULL si se produce algún error */
Point* map_getNeighborPoint(const Map* map, const Point* point, const Move mov)
{
  int nCols, x, y, p;

  if (!map || !point)
    return NULL;

  nCols = map_getNcols(map);

  x = point_getCoordinateX(point);
  y = point_getCoordinateY(point);

  p = y * nCols + x;

  if (mov == UP)
    return map->data[p-nCols];
  else if (mov == DOWN)
    return map->data[p+nCols];
  else if (mov == LEFT)
    return map->data[p-1];
  else if (mov == RIGHT)
    return map->data[p+1];
  else if (mov == STAY)
    return map->data[p];
  else
    return NULL;
}


/* Indica el tamaño de un mapa, devuelve NULL si se produce algún error */
Status map_setSize(Map* map, int nrow, int ncol)
{
  if (!map)
    return ERROR;

  map->nRows = nrow;
  map->nCols = ncol;
  return OK;
}

/* Añade un punto a un mapa dado reservando nueva memoria (de ahí que el
argumento sea declarado como const), o modifica el punto si ya se encuentra.
Debe comprobar si el punto es de tipo Output o Input para guardarlo como
corresponda. Devuelve OK si todo ha ido correctamente (se ha podido
incluir/actualizar el punto). */
Status map_setPoint(Map* map, const Point* point)
{
  int dataPosition;

  if(!map || !point)
    return ERROR;

  dataPosition = point_getCoordinateY(point) * map_getNcols(map) +
                 point_getCoordinateX(point);

  if (!(map->data[dataPosition]))
  {
    /* Nuevo point (con reserva de memoria), que es como el que pasan */
    map->data[dataPosition] = point_copy(point);

    if(point_getSymbol(map->data[dataPosition]) == 'i')
      map->input = map->data[dataPosition];

    if(point_getSymbol(map->data[dataPosition]) == 'o')
      map->output = map->data[dataPosition];
  }
  else
  {
    point_setSymbol(map->data[dataPosition], point_getSymbol(point));
  }
  return OK;
}

/* Imprime en un fichero dado los data de un mapa. Además,devolverá el número
de caracteres que se han escrito con éxito*/
int map_print(FILE* f, const Map* map)
{
  int i, j, escritos, nrows, ncols;
  escritos = 0;

  if (!map || !f)
    return ERROR;

  nrows = map_getNrows(map);
  ncols = map_getNcols(map);

  for(i = 0; i < nrows; i++)
  {
    fprintf(f, "\n");
    for(j = 0; j < ncols; j++)
      escritos += fprintf(f, "%c ", point_getSymbol(map->data[i*ncols+j]));
  }

  fprintf(f, "\n");
  return escritos;
}


Status map_read (FILE *f, Map *map)
{
 char buff[MAX_MAP];
 int i, j, nrows, ncols;
 Point *temp = NULL;

 if (!map || !f)
  return ERROR;

 /*creamos punto que se utiliza como buffer*/
 temp = point_ini(0, 0, ERRORCHAR);
 if (!temp)
  return ERROR;

 /* asignamos dimensión al mapa */
 fgets(buff, MAX_MAP, f);
 sscanf(buff, "%d %d", &nrows, &ncols);

 if (map_setSize (map, nrows, ncols) == ERROR)
   return ERROR;

 /* leemos el fichero linea a linea */
 for(i=0; i < nrows;i++)
 {
   fgets(buff, MAX_MAP, f);
   for (j=0; j < ncols; j++)
   {
     /* ajustamos los atributos del punto leído */
     point_setCoordinateX(temp, j);
     point_setCoordinateY(temp, i);
     point_setSymbol(temp, buff[j]);

     /* insertamos el punto en el mapa */
     map_setPoint(map, temp);
   }
 }

 /* libera recursos */
 point_destroy(temp);
 /* no cerramos el fichero ya que lo han abierto fuera */
 return OK;
}
