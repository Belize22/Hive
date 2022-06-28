#include "BeetleMovementStrategy.h"
#include "Board.h"

BeetleMovementStrategy::BeetleMovementStrategy() {

}

BeetleMovementStrategy::BeetleMovementStrategy(Board* board) {
	_board = board;
}

bool BeetleMovementStrategy::isMovementProper(GamePiece* gamePiece, Coordinate* coordinate)
{
	std::cout << "Moving Beetle!" << std::endl;
	return true; //TODO: Implement this function!
}
