#include <stdio.h>
#include <stdlib.h>
#include "stack_element.h"
#include "element.h"
#include "types.h"
#include "map.h"
#include "point.h"


/* Añadir a argumentos: Stack * camino*/
/* Cambiar: que devuelva Bool*/
/* Objetivo: Si hay camino se imprime, y si no, no imprimimos nada */
Point * deep_search(Map * map, Point * point)
{
  Stack * pila = NULL;
  Status flag = ERROR;
  Point * v = NULL, * w = NULL;
  Element * ele_pop = NULL, * ele_push = NULL;
  Move i;

  if (!map || !point)
    return NULL;

  pila = stack_ini();
  if(!pila)
    return NULL;

  ele_push = element_ini();
  if(!ele_push)
    return NULL;

  element_setInfo(ele_push, point);
  flag = stack_push(pila, ele_push);

  while(stack_isEmpty(pila) == FALSE && flag == OK)
  {
    ele_pop = stack_pop(pila);
    v = (Point *)element_getInfo(ele_pop);

    if(point_getSymbol(v) != VISITED)
    {
      point_setSymbol(v, VISITED);
      map_setPoint(map, v);
      for(i=0; i<5; i++)
      {
        w = map_getNeighborPoint(map, v, i);
        if(!w) return NULL;
        if(point_isOutput(w) == TRUE)
        {
          return w;
        }
        else if(point_isSpace(w) == TRUE)
        {
          ele_push = element_ini();
          if(!ele_push) return NULL;
          element_setInfo(ele_push, w);
          stack_push(pila, ele_push);
        }
      }
    }
  }

  stack_destroy(pila);

  point_destroy(v);
  point_destroy(w);
  return NULL;
}



int main(int argc, char const *argv[])
{
  Map * map = NULL;
  Point * input = NULL, * output = NULL;
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

  output = deep_search(map, input);
  if(!output)
    return ERROR;

  if(output == map_getOutput(map))
    printf("Es posible encontrar un camino\n");
  else
    printf("No es posible encontrar un camino\n");

  fclose(file);
  point_destroy(input);
  map_free(map);

  return 0;
}
