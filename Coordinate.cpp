#include "Coordinate.h"

Coordinate::Coordinate() {
	setCoordinate(new int(0), new int(0), new int(0));
}

Coordinate::Coordinate(int* x, int* y, int* z) {
	setCoordinate(new int(*x), new int(*y), new int(*z));
}

Coordinate::~Coordinate() {
	delete _x;
	delete _y;
	delete _z;
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

void Coordinate::incrementZ() {
	(*_z)++; //Needed to find coordinate above an occupied spot that a Beetle will go onto.
}

void Coordinate::setCoordinate(int* x, int* y, int* z) {
	_x = x;
	_y = y;
	_z = z;
}

std::string Coordinate::toString() {
	return std::to_string(*_x) + ", " + std::to_string(*_y) + ", " + std::to_string(*_z);
};

Coordinate* Coordinate::getOffsetCoordinate(Coordinate* originalCoordinate, HexDirection direction)
{
	int* newX = new int(originalCoordinate->getX() + horizontalDirectionOffset(direction));
	int* newY = new int(originalCoordinate->getY() + verticalDirectionOffset(direction, originalCoordinate->getX()));
	int* newZ = new int(originalCoordinate->getZ());

	return new Coordinate(newX, newY, newZ);
}

int Coordinate::horizontalDirectionOffset(HexDirection direction) {
	switch (direction) {
		case UP_RIGHT:
			return 1;
		case DOWN_RIGHT:
			return 1;
		case DOWN_LEFT:
			return -1;
		case UP_LEFT:
			return -1;
		default:
			return 0;
	}
}

int Coordinate::verticalDirectionOffset(HexDirection direction, int xValue) {
	switch (direction) {
		case UP:
			return -1;
		case UP_RIGHT:
		case UP_LEFT:
			return (xValue % 2 == 0 ? -1 : 0);
		case DOWN_RIGHT:
		case DOWN_LEFT:
			return (xValue % 2 == 0 ? 0 : 1);
		case DOWN:
			return 1;
		default:
			return 0;
	}
}

bool Coordinate::operator==(const Coordinate& other) {
	return *_x == *other._x && *_y == *other._y && *other._z == *other._z;
}

bool Coordinate::operator<(const Coordinate& other) {
	return (*_x != *other._x ? *_x < *other._x : (*_y != *other._y ? *_y < *other._y : *_z < *other._z));
}