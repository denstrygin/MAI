all: main.o
	g++ main.o -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -f *.o main