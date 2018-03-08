#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "stack_element.h"
#include "types.h"
#include "map.h"

int main(int argc, char *argv[]) {
  Stack * points;
  Point * point;
  int x, y;
  FILE * file;
  Map * map;

  if(argc < 2)
  {
    fprintf(stderr, "Use %s <data_file>\n", argv[0]);
    return ERROR;
  }

  file = fopen(argv[1], "r");
  if(!file)
  {
    fprintf(stderr, "Couldn't open %s\n", argv[1]);
    return ERROR;
  }

  map = map_ini();
  if(!map) 
		return ERROR;

  if(map_read(file, map)==ERROR)
		return ERROR;

  points = stack_ini();
  if(!points)
		return ERROR;

  for(x=0; x<map_getNrows(map); x++)
  {
    for(y=0; y<map_getNcols(map); y++)
    {
      point = point_ini(x, y, '*');
      if(!point) 
				return ERROR;
      point = map_getNeighborPoint(map, point, STAY);
      if(stack_push(points, point) == ERROR) 
				return ERROR;
    }
  }

  if(!stack_print(stdout, points))
		return ERROR;

  point_destroy(point);
  stack_free(points);
  map_destroy(map);
  fclose(file);

  return 0;
}
