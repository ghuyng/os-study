all: main.o ex1.o my_malloc.o
	gcc -o ex1 main.o ex1.o my_malloc.o

main.o: main.c ex1.h
	gcc -c main.c

ex1.o: ex1.c ex1.h my_malloc.h
	gcc -c ex1.c

my_malloc.o: my_malloc.c my_malloc.h
	gcc -c my_malloc.c

clean:
	rm -rf *.o ex1
