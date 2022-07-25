#include "GrasshopperMovementStrategy.h"
#include "Board.h"

GrasshopperMovementStrategy::GrasshopperMovementStrategy() {

}

GrasshopperMovementStrategy::GrasshopperMovementStrategy(Board* board) {
	_board = board;
}

bool GrasshopperMovementStrategy::pieceCanMoveOnOccupiedSpace(HexNode* target)
{
	std::cout << "Destination spot is occupied!" << std::endl;
	return false; //Only Beetle can move onto an occupied space!
}

bool GrasshopperMovementStrategy::isMovementProper(HexNode* source, HexNode& destination)
{
	std::cout << "Moving Grasshopper!" << std::endl;
	return true; //TODO: Implement this function!
}
