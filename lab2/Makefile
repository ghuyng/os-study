all: main.o readline.o findsubstr.o
	gcc -o mygrep main.o readline.o findsubstr.o

main.o: main.c readline.h findsubstr.h
	gcc -c main.c

readline.o: readline.c readline.h
	gcc -c readline.c

findsubstr.o: findsubstr.c findsubstr.h
	gcc -c findsubstr.c

clean: 
	rm -f *.o mygrep
