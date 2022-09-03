#include "SoldierAntMovementStrategy.h"
#include "Board.h"

SoldierAntMovementStrategy::SoldierAntMovementStrategy() {
	maxDistance = INT_MAX;
}

SoldierAntMovementStrategy::SoldierAntMovementStrategy(Board* board) {
	_board = board;
	maxDistance = INT_MAX;
}

std::vector<Coordinate*>* SoldierAntMovementStrategy::getCandidates(HexNode* start, Player* player) {
	return nullptr;
}



bool SoldierAntMovementStrategy::distanceConditionSatisfied(int* distance) {
	return true; //Any distance is good!
}
