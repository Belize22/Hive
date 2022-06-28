#include "SpiderMovementStrategy.h"
#include "Board.h"

SpiderMovementStrategy::SpiderMovementStrategy() {

}

SpiderMovementStrategy::SpiderMovementStrategy(Board* board) {
	_board = board;
}

bool SpiderMovementStrategy::isMovementProper(GamePiece* gamePiece, Coordinate* coordinate)
{
	std::cout << "Moving Spider!" << std::endl;
	return true; //TODO: Implement this function!
}
