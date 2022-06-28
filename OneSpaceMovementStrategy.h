#ifndef ONE_SPACE_MOVEMENT_STRATEGY
#define ONE_SPACE_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class OneSpaceMovementStrategy : public MovementStrategy
{
public:
	OneSpaceMovementStrategy();
	OneSpaceMovementStrategy(Board* board);
	bool areSourceAndDestinationAdjacent(GamePiece* gamePiece, Coordinate* coordinate);
	virtual bool isMovementProper(GamePiece* gamePiece, Coordinate* coordinate) = 0;
};

#endif