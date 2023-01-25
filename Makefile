PRG = cut
CC = gcc
CFLAGS = -std=c99 -lpthread

$(PRG): main.o analyzer.o reader.o
	$(CC) -o $(PRG) main.c analyzer.c reader.c printer.c $(CFLAGS)

clean:
	rm *.o $(PRG)