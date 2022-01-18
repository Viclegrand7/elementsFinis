#ifndef BV_TD_TRIANGLE_HH
#define BV_TD_TRIANGLE_HH

#include "point.hh"

class Triangle {
	Point *att_points[3];
public:
	Point *operator[] (unsigned int index) {return index < 3 ? att_points[index] : nullptr;}
	Triangle(Point *first, Point *second, Point *third) {att_points[0] = first; att_points[1] = second; att_points[2] = third;}
	friend std :: ostream &operator<<(std :: ostream &out, Triangle &self) {
		return out << self.att_points[0]->getId() << '\t' << self.att_points[1]->getId() << '\t' << self.att_points[2]->getId();
	}
};

#endif /* BV_TD_TRIANGLE_HH */