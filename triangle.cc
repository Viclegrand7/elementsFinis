#include "triangle.hh"

Triangle :: Triangle(Point *first, Point *second, Point *third) 
	: att_points{first, second, third} {
	att_surface = :: abs((third->getX() - second->getX()) * (first->getY() - third->getY()) - 
		(third->getY() - second->getY()) * (first->getX() - third->getX())) / 2.f;
}

double Triangle :: gradPhi(int i) {
	Point *p0, *p1;
	p0 = att_points[(i + 1) % 3];	p1 = att_points[(i + 2) % 3];
	return :: abs((p0->getY() - p1->getY()) - (p0->getX() - p1->getX())) / (2 * att_surface);
}

double Triangle :: phi(double x, double y, int i) {
	Point *p0, *p1;
	p0 = att_points[(i + 1) % 3];	p1 = att_points[(i + 2) % 3];
	return :: abs((p0->getX() - p1->getX()) * (y - p0->getY()) - 
		(p0->getY() - p1->getY()) * (x - p0->getX())) / (2 * att_surface);
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

