CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
all: p2_e2 p2_e3
p2_e2: element-int.o stack_element.o p2_e2.o point.o map.o
	$(CC) $(CFLAGS) element-int.o stack_element.o p2_e2.o point.o map.o -o p2_e2
p2_e3: p2_e3.o element-int.o stack_element.o point.o map.o
	$(CC) $(CFLAGS) element-int.o stack_element.o p2_e3.o point.o map.o -o p2_e3

#Objetos
element-int.o: element-int.c element.h stack_element.h types.h point.h
	$(CC) $(CFLAGS) -c element-int.c

stack_element.o: stack_element.c element.h stack_element.h types.h
	$(CC) $(CFLAGS) -c stack_element.c

p2_e2.o: p2_e2.c element.h stack_element.h types.h map.h point.h
	$(CC) $(CFLAGS) -c p2_e2.c

point.o: point.c point.h types.h
	$(CC) $(CFLAGS) -c point.c

map.o: map.c map.h types.h point.h
	$(CC) $(CFLAGS) -c map.c

p2_e3.o: p2_e3.c element.h stack_element.h types.h map.h point.h
	$(CC) $(CFLAGS) -c p2_e3.c

#Borrar objetos
clean:
	rm -f *.o
