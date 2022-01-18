#ifndef BV_TD_MESH_HH
#define BV_TD_MESH_HH

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "point.hh"
#include "triangle.hh"

class Mesh {
	std :: vector <Point *> att_pointList;
	std :: vector <Triangle *> att_triangleList;
	size_t att_freedomDegrees;
	//SparseMatrix <double> *att_A;
	//SparseMatrix <double> *att_F;
public:
	Mesh(std::string filename);
	double **assemble(); //x and *x will need to be freed
};

#endif /* BV_TD_MESH_HH */