#ifndef __VORONOI_H
#define __VORONOI_H
	typedef struct s_point {
		double x, y;
	} point;

	typedef struct s_helement {
		point pnt;
		double y;
		int type;
		struct dc_list *arc;
	} h_element;

	typedef struct vedge {
		point origin;
		struct vface *iface;
		struct vedge *twin, *next, *prev;
		int f;
	} half_edge;

	typedef struct vface {
		point site;
		struct vedge *edge;
		unsigned int is_ear:1;
	} face;

	typedef struct dc_list {
		struct dc_list *prev, *next;
		h_element *circle;
		point site;
		struct vface *f;
		struct vedge *e1, *e2;
	} sweep_line;

	extern int np, heap_size, heap_elem, p;
	extern face *voronoi;
	extern sweep_line *parabole;
	extern h_element **site_heap;
	double sweep_coord, xmin, xmax, ymin, ymax;

	//heap.c
	#define PARENT(i) ((i-1)/2)
	#define LEFT(i) (2*i+1)
	#define RIGHT(i) (2*(i+1))
	void max_heapify(int);
	h_element heap_extractmax();
	void heap_up(int);
	void heap_insert(h_element *);
	
	//geometry.c
	point geom_breakpoint(point *, point *);
	int geom_intersection(sweep_line *, point *, point *);
	void circle_event(sweep_line *);
	int circle(point, point, point, double *, point *);
	
	//dclist.c
	void add_parabole(point *);
	void del_parabole(sweep_line *);
	
	//python.c
	void generate_python_voronoi(face *, double, double, double, double);
	void generate_python_chull(face *, double, double, double, double);

#endif
