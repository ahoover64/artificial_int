CC=clang++
CFLAGS = -I. -std=c++11 -c -Wall -fPIC -g
SOURCES=$(wildcard *.cpp)

DEPS = Edge.h Vertex.h Graph.h
OBJ = Graph.o

.PHONY : all

all: %.o: %.cpp $(DEPS)
	$(CC) -c $< $(CFLAGS) $(SOURCES)

clean:
	rm -fr *.o
	rm -fr a.out
