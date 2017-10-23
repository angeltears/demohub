severt:severt.o fifo.o
	gcc -o severt severt.o fifo.o
client:client.o fifo.o
	gcc -o client client.o fifo.o
severt.o:severt.c
	gcc -o severt.o -c severt.c
fifo.o:fifo.c
	gcc -o fifo.o -c fifo.c
client.o:client.c
	gcc -o client.o -c client.c
clean:
	rm *.o severt client
