#include "MultiSpaceMovementStrategy.h"
#include "Board.h"

MultiSpaceMovementStrategy::MultiSpaceMovementStrategy() {

}

MultiSpaceMovementStrategy::MultiSpaceMovementStrategy(Board* board) {
	_board = board;
}

bool MultiSpaceMovementStrategy::destinationDetectableByDFS(GamePiece* gamePiece, Coordinate* coordinate)
{
	return true; //TODO: Implement this function!
}
