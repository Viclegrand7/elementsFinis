#include "mesh.hh"

double **Mesh :: assemble() {
	if (att_A)
		free(att_A);
	if (att_F)
		free(att_F);
	att_A = new SparseMatrix <double> (att_freedomDegrees, att_freedomDegrees);
	att_F = new SparseMatrix <double> (att_freedomDegrees, 1);
}