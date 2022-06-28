#ifndef SPIDER_MOVEMENT_STRATEGY
#define SPIDER_MOVEMENT_STRATEGY

class Board;
#include "MultiSpaceMovementStrategy.h"

class SpiderMovementStrategy : public MultiSpaceMovementStrategy
{
public:
	SpiderMovementStrategy();
	SpiderMovementStrategy(Board* board);
	bool isMovementProper(GamePiece* gamePiece, Coordinate* coordinate);
};

#endif
