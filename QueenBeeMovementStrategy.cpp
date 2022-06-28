#include "QueenBeeMovementStrategy.h"
#include "Board.h"

QueenBeeMovementStrategy::QueenBeeMovementStrategy() {

}

QueenBeeMovementStrategy::QueenBeeMovementStrategy(Board* board) {
	_board = board;
}

bool QueenBeeMovementStrategy::isMovementProper(GamePiece* gamePiece, Coordinate* coordinate)
{
	std::cout << "Moving Queen Bee!" << std::endl;
	return true; //TODO: Implement this function!
}
