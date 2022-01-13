#ifndef MOVEMENT_STRATEGY
#define MOVEMENT_STRATEGY

class Board;
#include "GamePieceStrategy.h"

#pragma once

class MovementStrategy : public GamePieceStrategy
{
public:
	MovementStrategy();
	MovementStrategy(Board* board);
	void unsetAdjacentSpots(HexNode* target);
	bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate);
	virtual std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player) = 0;
};

#endif
