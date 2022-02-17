#include "mesh.hh"
#include <string>
#include <iostream>
#include <vector>



long long Point :: globalId = -1;
long long Point :: globalDdl = 0;






int main() {
	Mesh mesh("simple_mesh.msh");
	mesh.test();
	mesh.assemble();
	mesh.solve();
	mesh.GNUPlotExport("test.dat");
	std :: cout << mesh.computeError() << std :: endl;

Point :: resetGlobals();
	Mesh half("simple_mesh.msh.msh");
	half.test();
	half.assemble();
	half.solve();
//	half.GNUPlotExport("test.dat");
	std :: cout << half.computeError() << std :: endl;

Point :: resetGlobals();
	Mesh quarterMesh("simple_mesh.msh.msh.msh");
	quarterMesh.test();
	quarterMesh.assemble();
	quarterMesh.solve();
//	quarterMesh.GNUPlotExport("test.dat");
	std :: cout << quarterMesh.computeError() << std :: endl;

}