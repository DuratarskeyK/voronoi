#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "voronoi.h"

int np;

int main() {
	int i,j,s=0;
	h_element *t, g;
	sweep_line *e;
	double xmin, xmax, ymin, ymax;
	
	freopen("tests/stress", "rt", stdin);
	
	scanf("%d", &np);

	voronoi = malloc(sizeof(face)*np);
	
	for(i = 0; i<np; ++i) {
		t = malloc(sizeof(h_element));
		scanf("%lf%lf", &t->pnt.x, &t->pnt.y);
		t->type = 0;
		t->y = t->pnt.y;
		heap_insert(t);
		
		if(!s) {
			xmin = t->pnt.x;
			ymin = t->pnt.y;
			xmax = t->pnt.x;
			ymax = t->pnt.y;
			s = 1;
		}
		else {
			if(xmin > t->pnt.x) xmin = t->pnt.x;
			if(ymin > t->pnt.y) ymin = t->pnt.y;
			if(xmax < t->pnt.x) xmax = t->pnt.x;
			if(ymax < t->pnt.y) ymax = t->pnt.y;
		}
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

	for(e = parabole; e; e = e->next) {
		if(e->e2) {
			e->e2->twin->origin = geom_breakpoint(&e->site, &e->next->site);
		}
	}
	
	generate_python_voronoi(voronoi, xmin, ymin, xmax, ymax);

	return 0;
}
