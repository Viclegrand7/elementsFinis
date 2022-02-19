#include "mesh.hh"
#include <string>
#include <iostream>
#include <vector>



long long Point :: globalId;
long long Point :: globalDdl;


double f(double x, double y) {
	return 0.;
}

double realSolutionSquare(double x, double y) {return 0.;} //Useless but needed



int main() {
	Point :: resetGlobals();
	Mesh mesh("simple_mesh.msh");
	mesh.test();
	mesh.assemble();
	mesh.solve();
//	std :: cout << "Error: " << mesh.computeError() << std :: endl;
	mesh.GNUPlotExport("final.dat");
	mesh.ParaviewExport("final.txt");

}
