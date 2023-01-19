PRG = cut
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -lpthread

$(PRG): main.o
	$(CC) -o $(PRG) main.c $(CFLAGS)

clean:
	rm *.o $(PRG)