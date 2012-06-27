#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "voronoi.h"

h_element **site_heap = NULL;
int heap_size = 0, heap_elem = 0;

void max_heapify(int i) {
	int l, r, largest;
	h_element *tmp;

	l = LEFT(i);
	r = RIGHT(i);

	if(l < heap_elem && site_heap[l]->y > site_heap[i]->y)
		largest = l;
	else
		largest = i;

	if(r < heap_elem && site_heap[r]->y > site_heap[largest]->y)
		largest = r;

	if(largest != i) {
		tmp = site_heap[i];
		site_heap[i] = site_heap[largest];
		site_heap[largest] = tmp;

		max_heapify(largest);
	}
}

h_element heap_extractmax() {
	h_element max;

	max.type = 2;
	if(!heap_elem)
		return max;

	max = *site_heap[0];
	site_heap[0] = site_heap[heap_elem-1];
	heap_elem--;
	max_heapify(0);

	return max;
}

void heap_up(int i) {
	int k;
	h_element *tmp;

	while(i>0 && site_heap[PARENT(i)]->y < site_heap[i]->y) {
		k = PARENT(i);
		tmp = site_heap[k];
		site_heap[k] = site_heap[i];
		site_heap[i] = tmp;
		i = PARENT(i);
	}
}

void heap_insert(h_element *elem) {
	double y;
	if(heap_elem == heap_size) {
		site_heap = realloc(site_heap, (heap_size+10)*sizeof(h_element));
		heap_size+=10;
	}

	site_heap[heap_elem] = elem;

	heap_up(heap_elem);

	heap_elem++;
}
