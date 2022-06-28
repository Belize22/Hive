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
	virtual bool isMovementProper(HexNode* source, HexNode* destination) = 0;
};

#endif