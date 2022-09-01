#ifndef SPIDER_MOVEMENT_STRATEGY
#define SPIDER_MOVEMENT_STRATEGY

class Board;
#include "MultiSpaceMovementStrategy.h"

const int DISTANCE_SPIDER_CAN_MOVE = 3;

class SpiderMovementStrategy : public MultiSpaceMovementStrategy {
	public:
		SpiderMovementStrategy();
		SpiderMovementStrategy(Board* board);
		bool distanceConditionSatisfied(int* distance);
};

#endif
