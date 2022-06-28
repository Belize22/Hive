#include "GrasshopperMovementStrategy.h"
#include "Board.h"

GrasshopperMovementStrategy::GrasshopperMovementStrategy() {

}

GrasshopperMovementStrategy::GrasshopperMovementStrategy(Board* board) {
	_board = board;
}

bool GrasshopperMovementStrategy::isMovementProper(GamePiece* gamePiece, Coordinate* coordinate)
{
	std::cout << "Moving Grasshopper!" << std::endl;
	return true; //TODO: Implement this function!
}
