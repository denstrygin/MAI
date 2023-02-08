GPPFLAGS = -std=c++11
SERVNANE = server
CLIENTNAME = client

all: server.o client.o server_func.o tree.o
	g++ $(GPPFLAGS) server.o server_func.o tree.o -o $(SERVNANE) -lzmq
	g++ $(GPPFLAGS) client.o server_func.o -o $(CLIENTNAME) -lzmq

server.o: server_func.h my_tree.h
	g++ $(GPPFLAGS) -c server.cpp -o server.o

client.o: server_func.h
	g++ $(GPPFLAGS) -c client.cpp -o client.o

server_func.o: server_func.h
	g++ $(GPPFLAGS) -c server_func.cpp -o server_func.o

tree.o: my_tree.h
	g++ $(GPPFLAGS) -c my_tree.cpp -o tree.o

clean:
	rm *.o $(CLIENTNAME) $(SERVNANE)