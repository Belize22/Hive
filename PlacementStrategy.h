#ifndef PLACEMENT_STRATEGY
#define PLACEMENT_STRATEGY

#pragma once

class Board;
#include "GamePieceStrategy.h"
#include "GamePiece.h"
#include "Coordinate.h"

class PlacementStrategy : public GamePieceStrategy
{
public:
	PlacementStrategy();
	PlacementStrategy(Board* board);
	bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate);
};
#endif