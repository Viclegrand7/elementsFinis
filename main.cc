#include "mesh.hh"
#include <string>
#include <iostream>
#include <vector>



long long Point :: globalId;
long long Point :: globalDdl;






int main() {
	Point :: resetGlobals();
	Mesh mesh("flat.msh");
	mesh.test();
	mesh.assemble();
	mesh.solve();
	mesh.GNUPlotExport("final.dat");
	mesh.ParaviewExport("final.txt");

}