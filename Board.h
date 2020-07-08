#pragma once
#ifndef BOARD
#define BOARD

#include <map>

#include "GamePiece.h"
#include "Coordinate.h"

class Board
{
private:
	std::map<int, int> _gamePieces;
	//std::map<GamePiece, Coordinate> _gamePieces;

public:
	Board();
	//void placeGamePiece(GamePiece * gamePiece);
	//void moveGamePiece(GamePiece * gamePiece);
};

#endif