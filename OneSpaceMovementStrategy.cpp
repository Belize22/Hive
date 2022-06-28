#include "OneSpaceMovementStrategy.h"
#include "Board.h"

OneSpaceMovementStrategy::OneSpaceMovementStrategy() {

}

OneSpaceMovementStrategy::OneSpaceMovementStrategy(Board* board) {
	_board = board;
}

bool OneSpaceMovementStrategy::areSourceAndDestinationAdjacent(GamePiece* gamePiece, Coordinate* coordinate)
{
	return true; //TODO: Implement this function!
}
