#include <stdio.h>
#include <stdlib.h>
#include "stack_element.h"
#include "point.h"

struct _Stack
{
  int top;
  Element* item[MAXSTACK];
};

/**------------------------------------------------------------------
Inicializa la pila reservando memoria. Salida: NULL si ha habido error o
la pila si ha ido bien
------------------------------------------------------------------*/
Stack * stack_ini()
{
  Stack * pila;

  pila = (Stack*)calloc(1, sizeof(Stack));
  if(pila == NULL)
    return NULL;

  pila->top = -1;

  return pila;
}

/**------------------------------------------------------------------
Elimina la pila Entrada: la pila que se va a eliminar
------------------------------------------------------------------*/
void stack_destroy(Stack * pila)
{
  int i;

  if(pila == NULL)
    return;

  for (i=0; i<MAXSTACK; i++)
  {
    element_destroy(pila->item[i]);
    pila->item[i] = NULL;
  }

  free(pila);
}

/**------------------------------------------------------------------
Inserta un elemento en la pila. Entrada: un elemento y la pila donde
insertarlo. Salida: ERROR si no logra insertarlo, OK si lo logra
------------------------------------------------------------------*/
Status stack_push(Stack * pila, const Element * ele)
{
  Element* local = NULL;

  if(pila == NULL || ele == NULL || stack_isFull(pila))
    return ERROR;

  local = element_copy(ele);
  if(local == NULL)
    return ERROR;

  pila->top++;
  pila->item[pila->top] = local;

  return OK;
}

/**------------------------------------------------------------------
Extrae un elemento en la pila. Entrada: la pila de donde extraerlo.
Salida: NULL si no logra extraerlo o elelemento extraido si lo
 logra. Nótese que la pila quedará modificada
------------------------------------------------------------------*/
Element * stack_pop(Stack * pila)
{
  Element* ele_top = NULL;

  if(pila == NULL || stack_isEmpty(pila) == TRUE)
    return NULL;

  ele_top = pila->item[pila->top];

  pila->item[pila->top] = NULL;

  pila->top--;

  return ele_top;
}

/**------------------------------------------------------------------
Copia un elemento (reservando memoria) sin modificar el top de
la pila. Entrada: la pila de donde copiarlo.Salida: NULL si no
logra copiarlo o el elemento si lo logra
------------------------------------------------------------------*/
Element * stack_top(const Stack * pila)
{
  Element * copia;

  if(pila == NULL)
    return NULL;

  copia = element_copy(pila->item[pila->top]);

  return copia;
}

/**------------------------------------------------------------------
Comprueba si la pila esta vacia. Entrada: pila.
Salida: TRUE si está vacia o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack * pila)
{
  if(pila == NULL)
    return FALSE;

  if(pila->top == -1)
    return TRUE;

  return FALSE;
}

/**------------------------------------------------------------------
Comprueba si la pila esta llena. Entrada: pila.
Salida: TRUE si está llena o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isFull(const Stack * pila)
{
  /* Parece extraño, pero si pila==NULL, no queremos que se pueda hacer push
    en ella, así que decimos que está llena (TRUE) */
  if(pila == NULL)
    return TRUE;

  if(pila->top == MAXSTACK)
    return TRUE;

  return FALSE;
}

/**------------------------------------------------------------------
Imprime toda la pila, colocando el elemento en la cima al principio de la impresión (y un elemento por línea).
Entrada: pila y fichero donde imprimirla. Salida: Devuelve el número de caracteres escritos.
------------------------------------------------------------------*/
int stack_print(FILE * f, const Stack * pila)
{
  int contador = 0, i;

  if(pila == NULL || f == NULL)
    return FALSE;

  for(i = pila->top; i >= 0; i--)
  {
    contador += point_print(f, (Point*)(pila->item[i]));
    printf("\n");
    /*fprintf(f, "[%d] \n", *(int*)element_getInfo(pila->item[i]));*/
  }

  return contador;
}
