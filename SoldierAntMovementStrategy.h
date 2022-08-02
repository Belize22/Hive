#ifndef SOLDIER_ANT_MOVEMENT_STRATEGY
#define SOLDIER_ANT_MOVEMENT_STRATEGY

class Board;
#include "MultiSpaceMovementStrategy.h"

class SoldierAntMovementStrategy : public MultiSpaceMovementStrategy
{
public:
	SoldierAntMovementStrategy();
	SoldierAntMovementStrategy(Board* board);
	bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate);
};

#endif
