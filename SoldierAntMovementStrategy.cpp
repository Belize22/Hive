#include "SoldierAntMovementStrategy.h"
#include "Board.h"

SoldierAntMovementStrategy::SoldierAntMovementStrategy() {

}

SoldierAntMovementStrategy::SoldierAntMovementStrategy(Board* board) {
	_board = board;
}

bool SoldierAntMovementStrategy::isMovementProper(HexNode* source, Coordinate& destinationCoordinate)
{
	std::cout << "Moving Soldier Ant!" << std::endl;
	return true; //TODO: Implement this function!
}
