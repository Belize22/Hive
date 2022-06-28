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
