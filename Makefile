all: voronoi

voronoi: main.o heap.o geometry.o dclist.o python.o
	gcc heap.o geometry.o dclist.o python.o main.o -o voronoi -lm

main.o: main.c
	gcc -c main.c

heap.o: heap.c
	gcc -c heap.c
	
geometry.o: geometry.c
	gcc -c geometry.c
	
dclist.o: dclist.c
	gcc -c dclist.c

python.o: python.c
	gcc -c python.c

run: clean voronoi
	./voronoi

clean:
	rm -f *.o voronoi
