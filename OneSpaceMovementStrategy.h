#ifndef ONE_SPACE_MOVEMENT_STRATEGY
#define ONE_SPACE_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class OneSpaceMovementStrategy : public MovementStrategy
{
public:
	OneSpaceMovementStrategy();
	OneSpaceMovementStrategy(Board* board);
	int directionOfAdjacentDestination(HexNode* source, HexNode* destination);
	bool FTMRespectedForSpecifiedDirection(HexNode* source, HexDirection direction);
	virtual bool isMovementProper(HexNode* source, HexNode* destination) = 0;
};

#endif