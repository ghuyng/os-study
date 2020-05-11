all : pi_serial pi_multi-thread

pi_serial: pi_serial.o
	gcc -o pi_serial pi_serial.o

pi_multi-thread: pi_multi-thread.o
	gcc -o pi_multi-thread pi_multi-thread.o

pi_serial.o: pi_serial.c
	gcc -c pi_serial.c

pi_multi-thread.o: pi_multi-thread.c
	gcc -c pi_multi-thread.c

clean:
	rm -rf *.o pi_serial pi_multi-thread
