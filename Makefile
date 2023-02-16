PRG = cut
CC = gcc
CFLAGS = -std=c99 -lpthread

$(PRG): main.o queue.o reader.o
	$(CC) -o $(PRG) main.c queue.c reader.c $(CFLAGS)

clean:
	rm *.o $(PRG)