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

std::string Coordinate::toString() {
	return std::to_string(*_x) + ", " + std::to_string(*_y) + ", " + std::to_string(*_z);
};

void Coordinate::offsetCoordinate(Coordinate* coordinate, HexDirection direction) {
	coordinate->setCoordinate(new int(coordinate->getX() + horizontalDirectionOffset(direction)),
		new int(coordinate->getY() + verticalDirectionOffset(direction, coordinate->getX())),
		new int(coordinate->getZ()));
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
		return (xValue % 2 == 0 ? -1 : 0);
	case DOWN_RIGHT:
		return xValue % 2 == 0 ? 0 : 1;
	case DOWN:
		return 1;
	case DOWN_LEFT:
		return (xValue % 2 == 0 ? 0 : 1);
	case UP_LEFT:
		return xValue % 2 == 0 ? -1 : 0;
	default:
		return 0;
	}
}

bool Coordinate::operator==(const Coordinate& other) {
	// z excluded for now. Will be explored when Beetle token is implemented.
	return *_x == *other._x && *_y == *other._y && *other._z == *other._z;
}

bool Coordinate::operator<(const Coordinate& other) {
	// priority is x, then y, then z.
	return (*_x != *other._x ? *_x < *other._x : (*_y != *other._y ? *_y < *other._y : *_z < *other._z));
}