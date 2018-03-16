#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "stack_element.h"
#include "types.h"
#include "map.h"

int main(int argc, char *argv[]) {
  Stack * pila;
  Point * point;
  int x, y;
  FILE * f;
  Map * mapa;
  Element* ele;

  if(argc < 2)
  {
    fprintf(stderr, "El programa se abre con: %s <data_file>\n", argv[0]);
    return ERROR;
  }

  f = fopen(argv[1], "r");
  if(!f)
  {
    fprintf(stderr, "No se pudo abrir %s\n", argv[1]);
    return ERROR;
  }

  mapa = map_ini();
  if(mapa == NULL)
		return ERROR;

  if(map_read(f, mapa) == ERROR)
		return ERROR;

  pila = stack_ini();
  if(pila == NULL)
		return ERROR;

  ele = element_ini();
  if(ele == NULL)
    return ERROR;

  for(x=0; x<map_getNrows(mapa); x++)
  {
    for(y=0; y<map_getNcols(mapa); y++)
    {
      point = point_ini(x, y, '*');
      if(point == NULL)
				return ERROR;

      point = map_getNeighborPoint(mapa, point, STAY);

      element_setInfo(ele, point);

      if(stack_push(pila, ele) == ERROR)
				return ERROR;
    }
  }

  if(!stack_print(stdout, pila))
		return ERROR;

  stack_destroy(pila);
  map_free(mapa);
  fclose(f);

  return 0;
}
