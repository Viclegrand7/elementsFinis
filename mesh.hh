#ifndef BV_TD_MESH_HH
#define BV_TD_MESH_HH

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/Dense>

#include <vtkType.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPoints.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkXMLUnstructuredGridWriter.h>

#include "point.hh"
#include "triangle.hh"

class Mesh {
	std :: vector <Point *> att_pointList;
	std :: vector <Triangle *> att_triangleList;
	size_t att_freedomDegrees;
	Eigen :: SparseMatrix <double> *att_A;
	Eigen :: VectorXd *att_F;
	Eigen :: VectorXd *att_X;
public:
	Mesh(std::string filename);
	~Mesh(); //delete each Point *
	void assemble();
	void VTKExport(const std :: string &fileName);
	void solve();
};

#endif /* BV_TD_MESH_HH */