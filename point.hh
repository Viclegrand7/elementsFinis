#ifndef BV_TD_POINT_HH
#define BV_TD_POINT_HH

#define BORDER_NO_CONDITION 0
#define BORDER_NEUMANN 1
#define BORDER_DIRICHLET_HOT 2
#define BORDER_DIRICHLET_COLD 4

#include <iostream>

class Point {
	double att_x;
	double att_y;
	unsigned char att_borderType;
	long long att_id;
	long long att_ddl;
public:
	static long long globalId;
	static long long globalDdl;
	double getX() {return att_x;}
	double getY() {return att_y;}
	void setBorderType(unsigned char label) {att_borderType = label;}
	unsigned char borderType() {return att_borderType;}
	long long getId() {return att_id;}
	long long getDdl() {return att_ddl;}
	Point(double x, double y, unsigned char borderType = BORDER_NO_CONDITION) : 
		att_x(x), att_y(y), att_borderType(borderType), att_id(++globalId) {
			att_ddl = (att_borderType == BORDER_NO_CONDITION || att_borderType == BORDER_NEUMANN) ? globalDdl++ : -1;
		}
	std :: ostream &operator<<(std :: ostream &out) {
		return out << att_x << '\t' << att_y;
	}
	void decreaseDdl() {if (att_ddl + 1) --att_ddl;}
	void deleteDdl() {att_ddl = -1;}
	static void resetGlobals() {
		globalId = -1;
		globalDdl = 0;
	}
};

#endif /* BV_TD_POINT_HH */