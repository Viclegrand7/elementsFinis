#ifndef BV_TD_POINT_HH
#define BV_TD_POINT_HH

#define BORDER_NO_CONDITION 0
#define BORDER_NEUMANN 1
#define BORDER_DIRICHLET 2

#include <iostream>

class Point {
	double att_x;
	double att_y;
	unsigned char att_borderType;
	static long long globalId;
	long long att_id;
	long long att_ddl;
public:
	static long long globalDdl;
	double getX() {return att_x;}
	double getY() {return att_y;}
	unsigned char borderType() {return att_borderType;}
	long long getId() {return att_id;}
	long long getDdl() {return att_ddl;}
	Point(double x, double y, unsigned char borderType = BORDER_NO_CONDITION) : 
		att_x(x), att_y(y), att_borderType(borderType), att_id(++globalId) {
			att_ddl = att_borderType == BORDER_NO_CONDITION ? ++globalDdl : -1;
		}
	std :: ostream &operator<<(std :: ostream &out) {
		return out << att_x << '\t' << att_y;
	}
};

#endif /* BV_TD_POINT_HH */