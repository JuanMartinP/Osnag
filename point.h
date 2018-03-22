#ifndef _POINT_
#define _POINT_

#include "types.h"

typedef struct _Point Point;


/* Constantes públicas que definen los tipos de puntos
que se permiten en un mapa */
#define ERRORCHAR 'E'
#define INPUT 'i'
#define VISITED 'v'
#define OUTPUT 'o'
#define BARRIER '+'
#define SPACE ' '



/* Inicializa un punto, reservando memoria y devolviendo el punto inicializado
si lo ha hecho correctamente o NULL si no */
Point * point_ini(int x, int y, char s);



/* Libera la memoria dinámica reservada para un punto*/
void point_destroy(Point * );



/* Devuelve la coordenada X de un punto dado, o -1 si se produce algún error */
int point_getCoordinateX(const Point * );



/* Devuelve la coordenada Y de un punto dado, o -1 si se produce algún error */
int point_getCoordinateY(const Point * );



/* Devuelve el símbolo de un punto dado, o ERRORCHAR si se produce algún error */
char point_getSymbol(const Point * );



/* Funciones derivadas que indican el tipo de punto que tenemos */
Bool point_isInput(Point* );

Bool point_isOutput(Point* );

Bool point_isBarrier(Point* );

Bool point_isSpace(Point* );

Bool point_isVisited(Point* );



/* Modifica la coordenda X de un punto dado,
devuelve ERROR si se produce algún error */
Status point_setCoordinateX(Point *, const int );



/* Modifica la coordenda Y de un punto dado,
devuelve ERROR si se produce algún error */
Status point_setCoordinateY(Point *, const int );



/* Modifica el símbolo de un punto dado,
devuelve ERROR si se produce algún error */
Status point_setSymbol(Point *, const char );



/* Devuelve TRUE si los dos puntos pasados como argumentos son iguales (revisando todos sus campos).
Devuelve FALSE en otro caso. */
Bool point_equals(const Point * , const Point * );



/* Copia los datos de un punto a otro devolviendo el punto copiado
(incluyendo la reserva de la memoria necesaria) si todo ha ido bien,
o NULL en otro caso */
Point * point_copy(const Point * );



/* Imprime en un fichero dado los datos de un punto con el siguiente formato:
[(x,y): symbol]. Por ejemplo, un punto con símbolo “*”, con coordenada X 3 e Y 7
se representará como [(3, 7): *]. Además, devolverá el número de caracteres
que se han escrito con éxito (mirar documentación de fprintf) */
int point_print(FILE *, const Point *);


#endif
