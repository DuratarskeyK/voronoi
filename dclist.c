#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "voronoi.h"

sweep_line *parabole = NULL;
face *voronoi;
int p = 0;

void add_parabole(point *def) {
	sweep_line *i, *new, *new2;
	half_edge *e1, *e2;
	point bp;
	if(!parabole) {
		parabole = malloc(sizeof(sweep_line));
		parabole->site = *def;
		parabole->prev = parabole->next = NULL;
		voronoi[p].site = *def;
		voronoi[p].last_edge = &voronoi[p].edges[0];
		parabole->f = &voronoi[p];
		p++;
	}
	else {
		for(i = parabole; i; i = i->next) {
			if(geom_intersection(i, def, &bp))
				break;
		}
		
		if(!i) {
			for(i = parabole; i->next; i = i->next);
			
			i->next = malloc(sizeof(sweep_line));
			new = i->next;
			new->site = *def;
			new->prev = i;
			new->next = NULL;
			bp.x = (def->x+i->site.x)/2; bp.y=def->y+i->site.y;
			
		}
		else {
			new2 = malloc(sizeof(sweep_line));
			memcpy(new2, i, sizeof(sweep_line));
			if(new2->next)
				new2->next->prev = new2;
			new = malloc(sizeof(sweep_line));	
			new->site = *def;
			new->prev = i;
			new->next = new2;
			i->next = new;
			new2->prev = new;
			
			voronoi[p].site = *def;
			voronoi[p].last_edge = &voronoi[p].edges[0];
			new->f = &voronoi[p];
			p++;
			
			e1 = malloc(sizeof(half_edge));
			e2 = malloc(sizeof(half_edge));
			e1->twin = e2;
			e2->twin = e1;
			e1->f = e2->f = 1;
			
			e1->iface = i->f;
			e2->iface = new->f;
			
			new->e2 = e2;
			new->e1 = e1;
			new->prev->e2 = e1;
			new->next->e1 = e2;
			
			*(i->f->last_edge++) = e1;
			*(new->f->last_edge++) = e2;
			
			*(i->f->last_edge) = *(new->f->last_edge) = NULL;
			
			circle_event(new->prev);
			circle_event(new->next);
		}
	}
}

void del_parabole(sweep_line *arc) {
	half_edge *e1, *e2;
	sweep_line *a,*e;
	
	e1 = malloc(sizeof(half_edge));
	e2 = malloc(sizeof(half_edge));

	a = arc;

	e1->origin = a->e1->twin->origin = a->e2->twin->origin = arc->circle->pnt;
	e1->f = e2->f = 1;
	
	a->prev->next = a->next;
	a->next->prev = a->prev;
	
	e1->iface = a->prev->f;
	e2->iface = a->next->f;
	e1->twin = e2;
	e2->twin = e1;
	*(a->prev->f->last_edge++) = e1;
	*(a->next->f->last_edge++) = e2;
	*a->next->f->last_edge = *a->prev->f->last_edge = NULL;
	
	a->prev->e2 = a->next->e1 = e1;

	circle_event(a->prev);
	circle_event(a->next);

	free(a);
}
