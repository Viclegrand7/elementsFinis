#ifndef BV_TD_MESH_HH
#define BV_TD_MESH_HH

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
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
	std :: vector <bool> att_isNeumann;
	size_t att_freedomDegrees;
	Eigen :: SparseMatrix <double> *att_A;
	Eigen :: VectorXd *att_F;
	Eigen :: VectorXd *att_X;
public:
	Mesh(std::string filename);
	~Mesh(); //delete each Point *
	void assemble();
	void VTKExport(const std :: string &fileName);
	void TRIExport(const std :: string &fileName);
	void GNUPlotExport(const std :: string &fileName);
	void ParaviewExport(const std :: string &fileName);
	void solve();
	void decreaseDdlFromPoint(unsigned int figure);
	double computeError();

	void test();
};

#endif /* BV_TD_MESH_HH */