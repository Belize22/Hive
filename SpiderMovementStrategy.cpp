#include "SpiderMovementStrategy.h"
#include "Board.h"

SpiderMovementStrategy::SpiderMovementStrategy() {

}

SpiderMovementStrategy::SpiderMovementStrategy(Board* board) {
	_board = board;
}

bool SpiderMovementStrategy::isMovementProper(HexNode* source, Coordinate& destinationCoordinate)
{
	std::cout << "Moving Spider!" << std::endl;
	return true; //TODO: Implement this function!
}
