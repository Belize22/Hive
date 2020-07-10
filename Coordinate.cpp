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