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
}