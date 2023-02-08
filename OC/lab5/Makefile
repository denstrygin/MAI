FLAGS = -g3 -Wall -pedantic
all: lab5_1 lab5_2
libdyn1.so: der_1.c gcf_simple.c lib1.c 
	gcc $(FLAGS) -fPIC -c der_1.c gcf_simple.c lib1.c
	gcc -shared der_1.o gcf_simple.o lib1.o -o libdyn1.so -lm
libdyn2.so: der_2.c gcf_evclid.c lib2.c
	gcc $(FLAGS) -fPIC -c der_2.c gcf_evclid.c lib2.c
	gcc -shared der_2.o gcf_evclid.o lib2.o -o libdyn2.so -lm
lab5_1: lab5_1.c lab5_1.h libdyn1.so
	gcc $(FLAGS) -c lab5_1.c
	gcc  lab5_1.o -L. libdyn1.so -Wl,-rpath,. -o lab5_1
lab5_2: lab5_2.c libdyn2.so 
	gcc $(FLAGS) -c lab5_2.c 
	gcc -o lab5_2  lab5_2.o -l dl
clear:
	rm *.o *.so lab5_1 lab5_2