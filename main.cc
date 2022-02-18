#include "mesh.hh"
#include <string>
#include <iostream>
#include <vector>



long long Point :: globalId;
long long Point :: globalDdl;






int main() {
	Point :: resetGlobals();
	Mesh mesh("simple_mesh.msh");
	mesh.test();
	mesh.assemble();
	mesh.solve();
	mesh.GNUPlotExport("test.dat");
	mesh.ParaviewExport("test.txt");
	std :: cout << mesh.computeError() << std :: endl;

	Point :: resetGlobals();
	Mesh half("simple_mesh.msh.msh");
	half.test();
	half.assemble();
	half.solve();
	half.GNUPlotExport("test.dat.dat");
	half.ParaviewExport("test.txt.txt");
	std :: cout << half.computeError() << std :: endl;

	Point :: resetGlobals();
	Mesh quarterMesh("simple_mesh.msh.msh.msh");
	quarterMesh.test();
	quarterMesh.assemble();
	quarterMesh.solve();
	quarterMesh.GNUPlotExport("test.dat.dat.dat");
	quarterMesh.ParaviewExport("test.txt.txt.txt");
	std :: cout << quarterMesh.computeError() << std :: endl;
}