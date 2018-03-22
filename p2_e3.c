#include <stdio.h>
#include <stdlib.h>
#include "stack_element.h"
#include "element.h"
#include "types.h"
#include "map.h"
#include "point.h"


/* Añadir a argumentos: Stack * camino*/
Bool deep_search(Map * map, Point * point)
{
  Stack * pila = NULL;
  Point * v = NULL, * w = NULL;
  Element * in = NULL, * ele_pop = NULL;
  Move i;

  if (!map || !point)
    return FALSE;

  pila = stack_ini();
  in = element_ini();

  if(!pila)
  {
    return FALSE;
  }

  element_setInfo(in, point);
  stack_push(pila, in);

  while (stack_isEmpty(pila) != TRUE)
  {
    printf("\n----------------------------------\n");
    ele_pop = stack_pop(pila);
    v = (Point *)element_getInfo(ele_pop);
    printf("\n>>>> Current space: ");
    point_print(stdout, v);

    if (point_getSymbol(v) != VISITED)
    {
      /* se visita el punto extraído de la pila */
      point_setSymbol(v, VISITED);

      /* se actualiza el punto en el mapa */
      map_setPoint(map, v);
      printf("\n");
      /*map_print(stdout, map);*/
      /* se añaden los vecinos para revisarlos posteriormente */
      for(i=0; i<=4; i++)
      {
        w = map_getNeighborPoint(map, v, i);

        if(!w)
          return FALSE;

        if(point_isOutput(w) == TRUE)
        {
          printf("\n----------------------------------\n");
          printf("\n>>>> Output  space: ");
          point_print(stdout, w);
          printf("\n\n");

          map_print(stdout, map);

          stack_destroy(pila);
          point_destroy(v);
          point_destroy(w);
          return TRUE;
        }
        else if(point_isSpace(w) == TRUE)
        {
          element_setInfo(ele_pop, w);
          stack_push(pila, ele_pop);
        }
      }
    }
/* element_destroy(ele_pop); */
  }
/*
  stack_destroy(pila);
  point_destroy(v);
  point_destroy(w);
*/
  return FALSE;
}




int main(int argc, char const *argv[])
{
  Map * map = NULL;
  Point * input = NULL;
  FILE * file = NULL;

  map = map_ini();
  if(!map)
    return ERROR;

  if(argc < 2)
  {
    fprintf(stderr, "El programa se abre con: %s <data_file>\n", argv[0]);
    return ERROR;
  }

  file = fopen(argv[1], "r");
  if(!file)
  {
    fprintf(stderr, "No se pudo abrir %s\n", argv[1]);
    return ERROR;
  }

  if(map_read(file, map) == ERROR)
    return ERROR;


  input = map_getInput(map);
  if(!input)
    return ERROR;


  if (deep_search(map, input)==TRUE)
  {
    fprintf(stdout, "\n\n----------------------------------");
    fprintf(stdout, "\n     RESULT:  THERE IS A WAY");
    fprintf(stdout, "\n----------------------------------\n\n");
  }
  else
  {
    fprintf(stdout, "\n\n----------------------------------");
    fprintf(stdout, "\n     RESULT:  THERE IS NO WAY");
    fprintf(stdout, "\n----------------------------------\n\n");
  }

  fclose(file);
  point_destroy(input);
  map_free(map);

  return 0;
}
