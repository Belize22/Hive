#include "MultiSpaceMovementStrategy.h"
#include "Board.h"

MultiSpaceMovementStrategy::MultiSpaceMovementStrategy() {

}

MultiSpaceMovementStrategy::MultiSpaceMovementStrategy(Board* board) {
	_board = board;
}

bool MultiSpaceMovementStrategy::destinationDetectableByDFS(HexNode* source, HexNode* destination)
{
	return true; //TODO: Implement this function!
}

bool MultiSpaceMovementStrategy::pieceCanMoveOnOccupiedSpace(HexNode* target)
{
	std::cout << "Destination spot is occupied!" << std::endl;
	return false; //Only Beetle can move onto an occupied space (this class is for Spider and Soldier Ant)!
}
