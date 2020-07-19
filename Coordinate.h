#ifndef COORDINATE
#define COORDINATE

class Coordinate
{
private:
	int* _x; //Dependent Hex Coordinate (always goes diagonal when going left or right).
	int* _y; //Independent Hex Coordinate (always goes up or down).
	int* _z; //Positive only. Some pieces can go on top of others.

public:
	Coordinate();
	Coordinate(int* x, int* y, int* z);
	int getX();
	int getY();
	int getZ();
	void setCoordinate(int* x, int* y, int* z);
	bool operator == (const Coordinate& other);
};

#endif