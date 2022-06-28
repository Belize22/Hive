#include "OneSpaceMovementStrategy.h"
#include "Board.h"

OneSpaceMovementStrategy::OneSpaceMovementStrategy() {

}

OneSpaceMovementStrategy::OneSpaceMovementStrategy(Board* board) {
	_board = board;
}

int OneSpaceMovementStrategy::directionOfAdjacentDestination(HexNode* source, HexNode* destination)
{
	HexNode* currentNode;
	Coordinate* currentCoordinate = source->getCoordinate();
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++)
	{
		currentNode = getAdjacentHexNode(currentCoordinate, i);
		if (currentNode == destination)
		{
			return i;
		}
	}
	return -1; //Means destination isn't adjacent.
}

bool OneSpaceMovementStrategy::FTMRespectedForSpecifiedDirection(HexNode* source, HexDirection direction)
{
	HexNode* currentNode;
	Coordinate* currentCoordinate = source->getCoordinate();

	//Check for occupied hex node in one adjacent direction.
	currentNode = getAdjacentHexNode(currentCoordinate, mod((static_cast<int>(direction))-1, ADJACENT_HEX_DIRECTIONS));
	if (currentNode->getGamePiece() == nullptr)
	{
		return true;
	}

	//Check for occupied hex node in other adjacent direction.
	currentNode = getAdjacentHexNode(currentCoordinate, mod((static_cast<int>(direction)) + 1, ADJACENT_HEX_DIRECTIONS));
	if (currentNode->getGamePiece() == nullptr)
	{
		return true;
	}

	return false; //Piece cannot move one direction if both its adjacent directions are occupied by game pieces!
}
