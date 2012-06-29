SOURCES=main.o heap.o geometry.o dclist.o python.o
CFLAGS=-Wall

all: $(SOURCES) link

link:
	gcc -lm -o voronoi $(SOURCES)

run: clean all
	./voronoi

clean:
	rm -f *.o voronoi
