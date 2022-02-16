#include "triangle.hh"

Triangle :: Triangle(Point *first, Point *second, Point *third) 
	: att_points{first, second, third} {
	att_surface =  ((third->getX() - second->getX()) * (first->getY() - third->getY()) - 
		(third->getY() - second->getY()) * (first->getX() - third->getX())) / 2;
}

std :: vector<double> Triangle :: gradPhi(int i) {
	std :: vector<double> tmp;
	switch (i) {
		case 0:
		{
			tmp.push_back((att_points[1]->getY() - att_points[2]->getY()) / (2 * att_surface));
			tmp.push_back((att_points[2]->getX() - att_points[1]->getX()) / (2 * att_surface));
			return tmp;
		}
		case 1:
		{
			tmp.push_back((att_points[2]->getY() - att_points[0]->getY()) / (2 * att_surface));
			tmp.push_back((att_points[0]->getX() - att_points[2]->getX()) / (2 * att_surface));
			return tmp;
		}
		case 2:
		{
			tmp.push_back((att_points[0]->getY() - att_points[1]->getY()) / (2 * att_surface));
			tmp.push_back((att_points[1]->getX() - att_points[0]->getX()) / (2 * att_surface));
			return tmp;
		}
		default:
			std :: cout << "i = " << i << " in gradPhi(x,y,i)" << std :: endl;
			exit(EXIT_FAILURE);
			break;
	}
}

double Triangle :: phi(double x, double y, int i) {
	switch (i) {
		case 0:
		{
			Point *p2(att_points[1]);
			Point *p3(att_points[2]);
			double p3_x(p3->getX());
			double p3_y(p3->getY());
			return ((p3_x - p2->getX()) * (y - p3_y) - (p3_y - p2->getY()) * (x - p3_x)) / (2 * att_surface);
		}
		case 1:
		{
			Point *p1(att_points[0]), *p3(att_points[2]);
			double p3_x(p3->getX()), p3_y(p3->getY());
			return ((p3_x - x) * (p1->getY() - p3_y) - (p3_y - y) * (p1->getX() - p3_x)) / (2 * att_surface);
		}
		case 2:
		{
			Point *p1(att_points[0]), *p2(att_points[1]);
			return ((x - p2->getX()) * (p1->getY() - y) - (y - p2->getY()) * (p1->getX() - x)) / (2 * att_surface);
		}
		default:
			std :: cout << "i = " << i << " in phi(x,y,i)" << std :: endl;
			exit(EXIT_FAILURE);
			break;
	}
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

