PRG = cut
CC = gcc
CFLAGS = -std=c99 -lpthread -Wall -Wextra

$(PRG): main.o queue.o reader.o analyzer.o
	$(CC) -o $(PRG) main.o queue.o reader.o analyzer.o $(CFLAGS)

main.o: main.c cut.h
	$(CC) -c main.c $(CFLAGS)

queue.o: queue.c cut.h
	$(CC) -c queue.c $(CFLAGS)

reader.o: reader.c cut.h
	$(CC) -c reader.c $(CFLAGS)

analyzer.o: analyzer.c cut.h
	$(CC) -c analyzer.c $(CFLAGS)

clean:
	rm *.o $(PRG)