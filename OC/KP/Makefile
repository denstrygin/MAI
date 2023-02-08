FLAGS = -g3 -Wall -pedantic
all: A B C
A.o: A.c
	gcc $(FLAGS) -c A.c 
B.o: B.c 
	gcc $(FLAGS) -c B.c 
C.o: C.c 
	gcc $(FLAGS) -c C.c 
A: A.o
	gcc -o A A.o
B: B.o
	gcc -o B B.o
C: C.o
	gcc -o C C.o
clear:
	rm *.o A B C