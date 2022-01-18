#include "mesh.hh"
#include <string>
#include <iostream>
#include <vector>



long long Point :: globalId = 0;






int main() {
	Mesh mesh("square.msh");
	mesh.assemble();
}