CPP=g++
CPPFLAGS=-c -Wall -pedantic -std=c++14 -O2
EXECUTABLE=solution

all: $(EXECUTABLE)
	
$(EXECUTABLE): main.o helpclass.o aposlo.o
	$(CPP) -O2 $^ -o $@ 

.cpp.o:
	$(CPP) $(CPPFLAGS) $< -o $@

main.o : aposlo.hpp helpclass.hpp
helpclass.o : helpclass.hpp
aposlo.o : aposlo.hpp helpclass.hpp

clean:
	rm -f *.o $(EXECUTABLE)
.PHONY: all clean