#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "point.h"


struct _Point
{
  char symbol;
  int x;
  int y;
};


/* s es el valor que hay en el punto */
Point * point_ini(int x, int y, char s)
{
  Point * newPoint = NULL;


  if (x < 0 || y < 0)
    return ERROR;

/* Reserva memoria y comprueba si se ha reservado correctamente */
  newPoint = (Point *) calloc(1, sizeof (Point));

  if (!newPoint)
    return NULL;

  point_setCoordinateX (newPoint, x);
  point_setCoordinateY (newPoint, y);
  point_setSymbol (newPoint, s);

  return newPoint;
}


/* Libera la memoria dinámica reservada para un punto*/
void point_destroy(Point* point)
{
  if (!point)
    return;

  free(point);
}


int point_getCoordinateX(const Point * p)
{
  return (p->x);
}



int point_getCoordinateY(const Point * p)
{
  return (p->y);
}



char point_getSymbol(const Point * p)
{
  return (p->symbol);
}


Bool point_isInput(Point* p)
{
  if (point_getSymbol(p) == 'i')
    return TRUE;
  else
    return FALSE;
}


Bool point_isOutput(Point* p)
{
  if (point_getSymbol(p) == 'o')
    return TRUE;
  else
    return FALSE;
}


Bool point_isBarrier(Point* p)
{
  if (point_getSymbol(p) == '+')
    return TRUE;
  else
    return FALSE;
}


Bool point_isSpace(Point* p)
{
  if (point_getSymbol(p) == ' ')
    return TRUE;
  else
    return FALSE;
}


Bool point_isVisited(Point* p)
{
  if (point_getSymbol(p) == 'v')
    return TRUE;
  else
    return FALSE;
}


/* Modifica la coordenda X de un punto dado,
devuelve ERROR si se produce algún error */
Status point_setCoordinateX(Point* point, const int x)
{
  if (!point)
    return ERROR;

  point->x = x;
  return OK;
}



/* Modifica la coordenda Y de un punto dado,
devuelve ERROR si se produce algún error */
Status point_setCoordinateY(Point* point, const int y)
{
  if (!point)
    return ERROR;

  point->y = y;
  return OK;
}


/* Modifica el símbolo de un punto dado,
devuelve ERROR si se produce algún error */
Status point_setSymbol(Point* point, const char symbol)
{
  if (!point)
    return ERROR;

  point->symbol = symbol;
  return OK;
}


/* Devuelve TRUE si los dos puntos pasados como argumentos son iguales (revisando todos sus campos).
Devuelve FALSE en otro caso. */
Bool point_equals(const Point* point1, const Point* point2)
{
  if (!point1 || !point2)
    return ERROR;

  if(point_getCoordinateX(point1) == point_getCoordinateX(point2) &&
     point_getCoordinateY(point1) == point_getCoordinateY(point2) &&
     point_getSymbol(point1) == point_getSymbol(point2))
  {
     return TRUE;
  }

  return FALSE;
}


/* Copia los datos de un punto a otro devolviendo el punto copiado
(incluyendo la reserva de la memoria necesaria) si todo ha ido bien,
o NULL en otro caso */
Point * point_copy(const Point * point)
{
  Point * pointCopy = NULL;

  if (!point)
    return NULL;

  pointCopy = point_ini(point_getCoordinateX(point), point_getCoordinateY(point), point_getSymbol(point));
  return pointCopy;
}


/* Imprime en un fichero dado los datos de un punto con el siguiente formato:
[(x,y): symbol]. Por ejemplo, un punto con símbolo “*”, con coordenada X 3 e Y 7
se representará como [(3, 7): *]. Además, devolverá el número de caracteres
que se han escrito con éxito (mirar documentación de fprintf) */
int point_print(FILE* f, const Point* point)
{
  if (!point || !f)
    return ERROR;

  return (fprintf(f, "[(%d,%d): %c]", point_getCoordinateX(point), point_getCoordinateY(point), point_getSymbol(point)));
}
