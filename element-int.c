#include <stdio.h>
#include <stdlib.h>
#include "element.h"

struct _Element
{
  Point* info;
};


/**------------------------------------------------------------------
Inicializa un elemento de pila. Salida: Puntero al elemento inicializado o
NULL en caso de error
------------------------------------------------------------------*/
Element * element_ini()
{
  Element * nwelement = NULL;

  nwelement = (Element*)calloc(1, sizeof(Element));

  nwelement->info = point_ini(0,0,0);

  if( nwelement == NULL)
    return NULL;

  return nwelement;
}

/**------------------------------------------------------------------
Elimina un elemento. Entrada: Elemento a destruir.
------------------------------------------------------------------*/
void element_destroy(Element * ele)
{
    if(ele==NULL)
      return ;

    point_destroy(ele->info);
    free(ele);
}

/**------------------------------------------------------------------
Modifica los datos de un elemento. Entrada: El elemento a modificar y el
 contenido a guardar en dicho elemento. Salida: OK o ERROR si ha habido error.
------------------------------------------------------------------*/
Status element_setInfo(Element * ele , void * inf)
{
  if(ele==NULL || inf == NULL)
    return ERROR;

  ele->info = inf;
  return OK;
}

/**------------------------------------------------------------------
Devuelve el contenido de Element. Entrada: El elemento. Salida: El contenido
de Element o NULL si ha habido error.
------------------------------------------------------------------*/
void * element_getInfo(Element * ele)
{
  return ele->info;
}

/**------------------------------------------------------------------
Copia un elemento en otro, reservando memoria. Entrada: el elemento a copiar.
Salida: Devuelve un puntero al elemento copiado o NULL en caso de error.
------------------------------------------------------------------*/
Element * element_copy(const Element * ele)
{
  Element * copia;

  if(ele == NULL)
    return NULL;

  copia = (Element*)calloc(1, sizeof(Element));

  copia->info = ele->info;

  return copia;
}

/**------------------------------------------------------------------
Compara dos elementos. Entrada: dos elementos a comparar. Salida: Devuelve
TRUE en caso de ser iguales y si no FALSE
------------------------------------------------------------------*/
Bool element_equals(const Element * ele1, const Element * ele2)
{
  if(ele1 == NULL || ele2 == NULL)
    return FALSE;

  if(point_equals(ele1->info, ele2->info) == TRUE)
    return TRUE;
  else
    return FALSE;
}

/**------------------------------------------------------------------
Imprime en un fichero ya abierto el elemento. Entrada: Fichero en el que se
 imprime y el elemento a imprimir. Salida: Devuelve el número de caracteres
escritos.
------------------------------------------------------------------*/
int element_print(FILE * f, const Element * ele)
{

  if (!ele || !f)
    return ERROR;

  return (point_print(f, ele->info));
}
