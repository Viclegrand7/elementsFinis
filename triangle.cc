#include "triangle.hh"

double Triangle :: surface() {
	Point *p0, *p1, *p2;
	p0 = att_points[0];	p1 = att_points[1];	p2 = att_points[2];
	return :: abs((p2->getX() - p1->getX()) * (p0->getY() - p2->getY()) - 
		(p2->getY() - p1->getY()) * (p0->getX() - p2->getX())) / 2.f;
}

double Triangle :: gradPhi(int i) {
	Point *p0, *p1;
	p0 = att_points[(i + 1) % 3];	p1 = att_points[(i + 2) % 3];
	return :: abs((p0->getY() - p1->getY()) - (p0->getX() - p1->getX())) / (2 * surface());
}

double Triangle :: phi(double x, double y, int i) {
	Point *p0, *p1;
	p0 = att_points[(i + 1) % 3];	p1 = att_points[(i + 2) % 3];
	return :: abs((p0->getX() - p1->getX()) * (y - p0->getY()) - 
		(p0->getY() - p1->getY()) * (x - p0->getX())) / (2 * surface());
}

double Triangle :: middleOpposedX(int i) {
	Point *p0, *p1;
	p0 = att_points[(i + 1) % 3];	p1 = att_points[(i + 2) % 3];
	return 0.5 * (p0->getX() + p1->getX()); 
}

double Triangle :: middleOpposedY(int i) {
	Point *p0, *p1;
	p0 = att_points[(i + 1) % 3];	p1 = att_points[(i + 2) % 3];
	return 0.5 * (p0->getY() + p1->getY()); 
}

