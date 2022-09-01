#include "SpiderMovementStrategy.h"
#include "Board.h"

SpiderMovementStrategy::SpiderMovementStrategy() {
	maxDistance = DISTANCE_SPIDER_CAN_MOVE;
}

SpiderMovementStrategy::SpiderMovementStrategy(Board* board) {
	_board = board;
	maxDistance = DISTANCE_SPIDER_CAN_MOVE;
}



bool SpiderMovementStrategy::distanceConditionSatisfied(int* distance) {
	return (*distance) == DISTANCE_SPIDER_CAN_MOVE;
}