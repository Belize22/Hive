#include "Coordinate.h"

Coordinate::Coordinate()
{
	setCoordinate(0, 0, 0);
}

Coordinate::Coordinate(int* x, int* y, int* z) {
	setCoordinate(x, y, z);
}

void Coordinate::setCoordinate(int* x, int* y, int* z) {
	_x = x;
	_y = y;
	_z = z;
}