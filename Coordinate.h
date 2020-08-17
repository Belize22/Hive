#ifndef COORDINATE
#define COORDINATE

#include <string>
#include "HexDirectionEnum.h"

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
	std::string toString();
	static void offsetCoordinate(Coordinate* coordinate, HexDirection direction);
	static int horizontalDirectionOffset(HexDirection direction);
	static int verticalDirectionOffset(HexDirection direction, int xValue);
	bool operator == (const Coordinate& other);
	bool operator < (const Coordinate& other);
};

#endif