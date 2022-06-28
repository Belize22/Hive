#ifndef MULTI_SPACE_MOVEMENT_STRATEGY
#define MULTI_SPACE_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class MultiSpaceMovementStrategy : public MovementStrategy
{
public:
	MultiSpaceMovementStrategy();
	MultiSpaceMovementStrategy(Board* board);
	bool destinationDetectableByDFS(GamePiece* gamePiece, Coordinate* coordinate);
	virtual bool isMovementProper(GamePiece* gamePiece, Coordinate* coordinate) = 0;
};

#endif