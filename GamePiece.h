#ifndef GAME_PIECE
#define GAME_PIECE

#include <map>

#include "Board.h"
#include "Coordinate.h"

class GamePiece
{
private:
	Coordinate * _position;

public:
	GamePiece(Coordinate* coordinate);
	Coordinate * getPosition();
};

#endif