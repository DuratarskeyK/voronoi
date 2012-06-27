#ifndef __PYTHONCODE_H
#define __PYTHONCODE_H
	#define HEADER "import matplotlib.pyplot as plt\nfrom matplotlib.path import Path\nimport matplotlib.patches as patches\n\n"

	#define VERTS_START "verts = [\n"
	
	#define SITES_START "sites = [\n"
	
	#define MAIN_CODE "codes = []\nfor i in range(len(verts)/2):\n\tcodes.extend([Path.MOVETO,Path.LINETO])\npath = Path(verts, codes)\n\nfig = plt.figure()\nax = fig.add_subplot(111)\npatch = patches.PathPatch(path, facecolor='orange', lw=0.5)\nax.add_patch(patch)\nfor i in sites:\n\tpatch = patches.Circle(i, radius=0.08)\n\tax.add_patch(patch)\n"
	
#endif
