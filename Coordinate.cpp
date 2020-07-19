#include "Coordinate.h"

Coordinate::Coordinate()
{
	setCoordinate(new int(0), new int(0), new int(0));
}

Coordinate::Coordinate(int* x, int* y, int* z) {
	setCoordinate(x, y, z);
}

int Coordinate::getX() {
	return *_x;
}

int Coordinate::getY() {
	return *_y;
}

int Coordinate::getZ() {
	return *_z;
}

void Coordinate::setCoordinate(int* x, int* y, int* z) {
	_x = x;
	_y = y;
	_z = z;
}

bool Coordinate::operator==(const Coordinate& other) {
	//z excluded for now. Will be explored when Beetle token is implemented.
	return *_x == *other._x && *_y == *other._y;
}