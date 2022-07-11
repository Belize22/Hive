#include "BeetleMovementStrategy.h"
#include "Board.h"

BeetleMovementStrategy::BeetleMovementStrategy() {

}

BeetleMovementStrategy::BeetleMovementStrategy(Board* board) {
	_board = board;
}

bool BeetleMovementStrategy::pieceCanMoveOnOccupiedSpace(HexNode* target)
{
	return true; //Only Beetle can move onto an occupied space!
}

bool BeetleMovementStrategy::isMovementProper(HexNode* source, HexNode* destination)
{
	std::cout << "Moving Beetle!" << std::endl;
	if (!spotIsAvailable(destination))
	{
		std::cout << "Beetle can move here after implementation is completed!" << std::endl;
		return false;
	}
	return true; //TODO: Implement this function!
}
