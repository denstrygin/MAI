CC=gcc
CFLAGS=-std=c99 -pedantic -Wall
LDFLAGS=
EXECUTABLE=prog
SRC=queue.c labra26.c
OBJ=$(SRC:.c=.o)

$(EXECUTABLE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

labra26.o: queue.h

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

queue.o: queue.h

clean:
	rm -f *.o $(EXECUTABLE)
