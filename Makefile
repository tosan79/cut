PRG = cut
CC = gcc
CFLAGS = -std=c99 -lpthread

$(PRG): main.o reader.o queue.o
	$(CC) -o $(PRG) main.c reader.c queue.c $(CFLAGS)

clean:
	rm *.o $(PRG)