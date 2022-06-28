#include "GrasshopperMovementStrategy.h"
#include "Board.h"

GrasshopperMovementStrategy::GrasshopperMovementStrategy() {

}

GrasshopperMovementStrategy::GrasshopperMovementStrategy(Board* board) {
	_board = board;
}

bool GrasshopperMovementStrategy::isMovementProper(HexNode* source, HexNode* destination)
{
	std::cout << "Moving Grasshopper!" << std::endl;
	return true; //TODO: Implement this function!
}
