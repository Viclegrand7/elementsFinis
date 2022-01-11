#include "triangle.hh"
#include <iostream>

long long Point :: globalId = -1;

int main() {
	Point a(1,2,3);
	Point b(2,3,4);
	Point c(3,4,5);
	Triangle test(&a,&b,&c);
	std :: cout << test[1]->getId() << std :: endl;
}