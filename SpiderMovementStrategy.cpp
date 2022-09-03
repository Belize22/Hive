#include "SpiderMovementStrategy.h"
#include "Board.h"

SpiderMovementStrategy::SpiderMovementStrategy() {
	maxDistance = DISTANCE_SPIDER_CAN_MOVE;
}

SpiderMovementStrategy::SpiderMovementStrategy(Board* board) {
	_board = board;
	maxDistance = DISTANCE_SPIDER_CAN_MOVE;
}

std::vector<Coordinate*>* SpiderMovementStrategy::getCandidates(HexNode* start, Player* player) {
	return nullptr;
}



bool SpiderMovementStrategy::distanceConditionSatisfied(int* distance) {
	return (*distance) == DISTANCE_SPIDER_CAN_MOVE;
}