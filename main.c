#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "voronoi.h"

int np;

int main() {
	int i;
	h_element *t, g;
	sweep_line *e;
	half_edge *first;
	
	freopen("tests/works1", "rt", stdin);
	
	scanf("%d", &np);

	voronoi = malloc(sizeof(face)*np);
	
	for(i = 0; i<np; ++i) {
		t = malloc(sizeof(h_element));
		scanf("%lf%lf", &t->pnt.x, &t->pnt.y);
		t->type = 0;
		t->y = t->pnt.y;
		heap_insert(t);
	}

	while((g = heap_extractmax()).type != 2) {
		sweep_coord = g.pnt.y;
		
		if(g.type == 3)
			continue;
		
		if(!g.type) 
			add_parabole(&g.pnt);
		else
			del_parabole(g.arc);
	}

	xmin-=25;
	ymin-=25;
	xmax+=25;
	ymax+=25;
	
	sweep_coord -= fabs(ymin*10);

	first = NULL;

	for(e = parabole; e; e = e->next) {
		if(e->e2) {
			e->f->is_ear = 1;
			e->e2->twin->f = 1;
			e->e2->twin->origin = geom_breakpoint(&e->site, &e->next->site);
			if(!first) {
				first = e->e2->twin;
			}
			else {
				e->e2->next = first;
				first->prev = e->e2->next;
				first = e->e2->twin;
			}
		}
	}
	
	parabole->e2->next = first;
	first->prev = parabole->e2;
	
	generate_python_chull(voronoi, xmin, ymin, xmax, ymax);

	return 0;
}
