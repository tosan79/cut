PRG = cut
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -lpthread

$(PRG): main.o analyzer.o reader.o
	$(CC) -o $(PRG) main.c analyzer.c reader.c $(CFLAGS)

clean:
	rm *.o $(PRG)