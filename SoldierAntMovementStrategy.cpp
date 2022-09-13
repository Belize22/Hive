#include "SoldierAntMovementStrategy.h"
#include "Board.h"

SoldierAntMovementStrategy::SoldierAntMovementStrategy() {
	maxDistance = INT_MAX;
}

SoldierAntMovementStrategy::SoldierAntMovementStrategy(Board* board) {
	_board = board;
	maxDistance = INT_MAX;
}



bool SoldierAntMovementStrategy::distanceConditionSatisfied(int* distance) {
	return (*distance) != 0; //Any distance except its current position is good!
}
