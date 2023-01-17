PRG = cut
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

cut: main.o
	$(CC) -o cut main.c $(CFLAGS)

clean:
	rm *.o $(PRG)