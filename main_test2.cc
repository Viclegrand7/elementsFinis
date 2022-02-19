#include "mesh.hh"
#include <string>
#include <iostream>
#include <vector>



long long Point :: globalId;
long long Point :: globalDdl;


double f(double x, double y) {
	return 2 * M_PI * M_PI * sin(M_PI * x) * cos(M_PI * y);
}


double realSolutionSquare(double x, double y) {
	return sin(M_PI * x) * cos(M_PI * y);
}


int main() {
	Point :: resetGlobals();
	Mesh mesh("simple_mesh.msh");
	mesh.test();
	mesh.assemble();
	mesh.solve();
	std :: cout << "Error: " << mesh.computeError() << std :: endl;
	mesh.GNUPlotExport("test.dat");
	mesh.ParaviewExport("final.txt");

	Point :: resetGlobals();
	Mesh halfMesh("half_second.msh");
	halfMesh.test();
	halfMesh.assemble();
	halfMesh.solve();
	std :: cout << "Error: " << halfMesh.computeError() << std :: endl;
	halfMesh.GNUPlotExport("test.dat.dat");
	halfMesh.ParaviewExport("final.txt.txt");

	Point :: resetGlobals();
	Mesh quarterMesh("quarter_second.msh");
	quarterMesh.test();
	quarterMesh.assemble();
	quarterMesh.solve();
	std :: cout << "Error: " << quarterMesh.computeError() << std :: endl;
	quarterMesh.GNUPlotExport("test.dat.dat.dat");
	quarterMesh.ParaviewExport("final.txt.txt.txt");
}