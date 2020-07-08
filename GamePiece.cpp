#include "GamePiece.h"

GamePiece::GamePiece(Coordinate* coordinate) {
	_position = coordinate;
};

Coordinate * GamePiece::getPosition() {
	return _position;
}