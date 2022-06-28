#include "QueenBeeMovementStrategy.h"
#include "Board.h"

QueenBeeMovementStrategy::QueenBeeMovementStrategy() {

}

QueenBeeMovementStrategy::QueenBeeMovementStrategy(Board* board) {
	_board = board;
}

bool QueenBeeMovementStrategy::isMovementProper(HexNode* source, HexNode* destination)
{
	std::cout << "Moving Queen Bee!" << std::endl;
	int direction = directionOfAdjacentDestination(source, destination);
	if (direction == -1)
	{
		std::cout << "Queen Bee cannot move more than 1 space!" << std::endl;
		return false;
	}
	if (!FTMRespectedForSpecifiedDirection(source, static_cast<HexDirection>(direction)))
	{
		std::cout << "Moving that direction violates Freedom To Move rule!" << std::endl;
		return false;
	}
	return true;
}
