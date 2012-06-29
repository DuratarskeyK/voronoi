#include <stdio.h>
#include <stdlib.h>
#include "voronoi.h"
#include "python_code.h"

void generate_python_voronoi(face *v, double xmin, double ymin, double xmax, double ymax) {
	int i;
	half_edge *t;
	
	freopen("/tmp/plot.py", "wt", stdout);
	
	puts(HEADER);
	puts(SITES_START);
	for(i = 0; i<p; i++) {
		printf("(%lf, %lf), \n", v[i].site.x, v[i].site.y);
	}
	printf("]\n\n");
	puts(VERTS_START);
	
	for(i = 0; i<p; i++) {
		for(t = voronoi[i].edge->next;;t = t->next) {
			if(t->f) {
				printf("(%.5lf, %.5lf),(%.5lf, %.5lf),\n", t->origin.x, t->origin.y, t->twin->origin.x, t->twin->origin.y);
				t->f =t->twin->f = 0;
			}
			if(t == voronoi[i].edge) break;
		}
	}

	printf("]\n\n");
	
	puts(MAIN_CODE);
	
	printf("ax.set_xlim(%.0lf,%.0lf)\nax.set_ylim(%.0lf,%.0lf)\nax.axes.get_yaxis().set_visible(False)\nax.axes.get_xaxis().set_visible(False)\nplt.show()\n", xmin, xmax, ymin, ymax);
	
	fclose(stdout);
	
	system("python /tmp/plot.py");
}

void generate_python_chull(face *v, double xmin, double ymin, double xmax, double ymax) {
	int i;
	half_edge *t;
	face *cf, *prev;
	
	freopen("/tmp/plot.py", "wt", stdout);
	
	puts(HEADER);
	puts(SITES_START);
	for(i = 0; i<p; i++) {
		printf("(%lf, %lf), \n", v[i].site.x, v[i].site.y);
	}
	printf("]\n\n");
	puts(VERTS_START);
	
	cf = &voronoi[0];
	prev = NULL;
	
	for(;;) {
			printf("(%.5lf, %.5lf),\n", cf->site.x, cf->site.y);
			for(t = cf->edge; ; t = t->next) {
				if(t->twin->iface->is_ear == 1 && prev != t->twin->iface) {
					prev = cf;
					cf = t->twin->iface;
					break;
				}
			}
			printf("(%.5lf, %.5lf),\n", cf->site.x, cf->site.y);
			if(cf == &voronoi[0]) break;
	}

	printf("]\n\n");
	
	puts(MAIN_CODE);
	
	printf("ax.set_xlim(%.0lf,%.0lf)\nax.set_ylim(%.0lf,%.0lf)\nax.axes.get_yaxis().set_visible(False)\nax.axes.get_xaxis().set_visible(False)\nplt.show()\n", xmin, xmax, ymin, ymax);
	
	fclose(stdout);
	
	system("python /tmp/plot.py");
}
