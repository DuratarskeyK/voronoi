#include <stdio.h>
#include "voronoi.h"
#include "python_code.h"

void generate_python(face *v, double xmin, double ymin, double xmax, double ymax) {
	int i, j;
	
	freopen("/tmp/plot.py", "wt", stdout);
	
	puts(HEADER);
	puts(SITES_START);
	for(i = 0; i<p; i++) {
		printf("(%lf, %lf), \n", v[i].site.x, v[i].site.y);
	}
	printf("]\n\n");
	puts(VERTS_START);
	
	for(i = 0; i<p; i++) {
		for(j = 0; v[i].edges[j] != NULL; j++) {
			if(v[i].edges[j]->f) {
				printf("(%.2lf, %.2lf),(%.2lf, %.2lf),\n", v[i].edges[j]->origin.x, v[i].edges[j]->origin.y, v[i].edges[j]->twin->origin.x, v[i].edges[j]->twin->origin.y);
				v[i].edges[j]->f =v[i].edges[j]->twin->f = 0;
			}
		}
	}

	printf("]\n\n");
	
	puts(MAIN_CODE);
	
	printf("ax.set_xlim(%.0lf,%.0lf)\nax.set_ylim(%.0lf,%.0lf)\nax.axes.get_yaxis().set_visible(False)\nax.axes.get_xaxis().set_visible(False)\nplt.show()\n", xmin, xmax, ymin, ymax);
	
	fclose(stdout);
	
	system("python /tmp/plot.py");
}
