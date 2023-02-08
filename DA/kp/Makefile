FLAGS = -std=c++11 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -O2
FILES = archiver.cpp LZ78.cpp

all: archiver
archiver: $(FILES)
	g++ $(FLAGS) $(FILES) -o archiver

clean:
	rm -f *.cmp *.dcmp archiver
