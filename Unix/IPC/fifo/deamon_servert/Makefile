severt:severt.o fifo.o
	gcc -o severt severt.o fifo.o
severt.o:deamon_severt.c
	gcc -o severt.o -c deamon_severt.c
fifo.o:fifo.c
	gcc -o fifo.o -c fifo.c
clean:
	rm *.o severt

