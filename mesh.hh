#ifndef BV_TD_MESH_HH
#define BV_TD_MESH_HH

#include <iostream>
#include "point.hh"
#include "triangle.hh"

class Mesh {
	Point *att_pointList;
	Triangle *att_triangleList;
public:
	Mesh(char *filename);
};

#endif /* BV_TD_MESH_HH */