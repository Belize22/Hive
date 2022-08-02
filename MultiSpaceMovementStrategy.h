#ifndef MULTI_SPACE_MOVEMENT_STRATEGY
#define MULTI_SPACE_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class MultiSpaceMovementStrategy : public MovementStrategy
{
public:
	MultiSpaceMovementStrategy();
	MultiSpaceMovementStrategy(Board* board);
	bool destinationDetectableByDFS(HexNode* source, HexNode* destination);
	bool pieceCanMoveOnOccupiedSpace(HexNode* target);
	virtual bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate) = 0;
};

#endif