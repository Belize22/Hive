#include "BeetleMovementStrategy.h"
#include "Board.h"

BeetleMovementStrategy::BeetleMovementStrategy() {

}

BeetleMovementStrategy::BeetleMovementStrategy(Board* board) {
	_board = board;
}

bool BeetleMovementStrategy::isMovementProper(HexNode* source, HexNode* destination)
{
	std::cout << "Moving Beetle!" << std::endl;
	return true; //TODO: Implement this function!
}
