#ifndef BV_TD_TRIANGLE_HH
#define BV_TD_TRIANGLE_HH

#include "point.hh"

class Triangle {
	Point *att_points[3];
	double att_surface;
public:
	Point *operator[] (unsigned int index) {return index < 3 ? att_points[index] : nullptr;}
	Triangle(Point *first, Point *second, Point *third);
	double getSurface() {return att_surface;}
	double gradPhi(int i);
	double phi(double x, double y, int i);
	friend std :: ostream &operator<<(std :: ostream &out, Triangle &self) {
		return out << self.att_points[0]->getId() << '\t' << self.att_points[1]->getId() << '\t' << self.att_points[2]->getId();
	}
	double middleOpposedX(int i);
	double middleOpposedY(int i);
};

#endif /* BV_TD_TRIANGLE_HH */