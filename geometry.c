#include <math.h>
#include <stdlib.h>
#include "voronoi.h"

point geom_breakpoint(point *p0, point *p1) {
	point res;
	double a,b,c,z0,z1, x1, x2, D;
	
	if(p0->y == p1->y) {
		res.x = (p0->x + p1->x)/2;
	}
	else if(p0->y == sweep_coord) {
		res.x = p0->x;
	}
	else if(p1->y == sweep_coord) {
		res.x = p1->x;
	}
	else {
		z0 = 2*(p0->y - sweep_coord);
		z1 = 2*(p1->y - sweep_coord);
		
		a = 1/z0 - 1/z1;
		b = -2 * (p0->x/z0 - p1->x/z1);
		c = (p0->x*p0->x + p0->y*p0->y - sweep_coord*sweep_coord)/z0 - (p1->x*p1->x + p1->y*p1->y - sweep_coord*sweep_coord)/z1;
		
		D = b*b-4*a*c;
		
		x1 = (-sqrt(D)-b)/(2*a);
		x2 = (sqrt(D)-b)/(2*a);
		if(p0->x <= x1 && x1 <= p1->x)
			res.x = x1;
		else res.x = x2;
	}
	res.y = (res.x*res.x - 2 * p0->x * res.x + p0->x * p0->x + p0->y * p0->y - sweep_coord * sweep_coord)/(2*p0->y - 2*sweep_coord);
	
	return res;
}

int geom_intersection(sweep_line *p, point *site, point *r) {
	double a, b;
	point res;
	
	if(p->site.y == site->y) return 0;
	
	if(p->prev)
		a = geom_breakpoint(&p->prev->site, &p->site).x;
	if(p->next)
		b = geom_breakpoint(&p->site, &p->next->site).x;

	if((!p->prev || a <= site->x) && (!p->next || site->x <= b)) {
		res.x = site->x;
		
		res.y = (res.x * res.x - 2 * p->site.x * res.x + p->site.x * p->site.x + p->site.y * p->site.y - sweep_coord*sweep_coord)/(2*p->site.y - 2*sweep_coord);
		
		*r = res;
		
		return 1;
	}

	return 0;
}

void circle_event(sweep_line *arc) {
	h_element *c_event;
	point a;
	double yc = 0;	

	if(!arc)
		return;

	if(arc->circle && arc->circle->type == 1) {
		arc->circle->type = 3;
	}

	arc->circle = NULL;
	
	if(!arc->prev || !arc->next)
		return;

	if(circle(arc->prev->site, arc->site, arc->next->site, &yc, &a) && yc <= sweep_coord) {
		c_event = malloc(sizeof(h_element));
		c_event->pnt = a;
		c_event->y = yc;
		c_event->type = 1;
		c_event->arc = arc;
		
		arc->circle = c_event;
		
		heap_insert(c_event);
	}

}

int circle(point a, point b, point c, double *y, point *o)
{	
	double A,B,C,D,E,F,G;
	
	if ((b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y) > 0)
		return 0;

	A = b.x - a.x;  
	B = b.y - a.y;
	C = c.x - a.x;
	D = c.y - a.y;
	E = A*(a.x+b.x) + B*(a.y+b.y);
	F = C*(a.x+c.x) + D*(a.y+c.y);
	G = 2*(A*(c.y-b.y) - B*(c.x-b.x));

	if (G == 0) return 0;

	o->x = (D*E-B*F)/G;
	o->y = (A*F-C*E)/G;

	*y = o->y - sqrt( pow(a.x - o->x, 2) + pow(a.y - o->y, 2) );
	return 1;
}
