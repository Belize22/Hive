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

bool OneSpaceMovementStrategy::areSourceAndDestinationAdjacent(HexNode* source, HexNode* destination, int direction)
{
	if (direction == -1)
	{
		return false;
	}

	return true;
}

bool OneSpaceMovementStrategy::FTMRespectedForSpecifiedDirection(HexNode* node, HexDirection direction)
{
	if (isAdjacentDirectionShorter(node, direction, -1)) //Left
	{
		return true;
	}
	if (isAdjacentDirectionShorter(node, direction, 1)) //Right
	{
		return true;
	}
	return false; //Piece cannot move one direction if both its adjacent directions are taller (or as tall) than the node!
}

bool OneSpaceMovementStrategy::isAdjacentDirectionShorter(HexNode* node, HexDirection direction, int directionOffset)
{
	Coordinate* currentCoordinate = new Coordinate(new int(node->getCoordinate()->getX()), new int(node->getCoordinate()->getY()), new int(node->getCoordinate()->getZ()));
	HexNode* currentNode = getAdjacentHexNode(currentCoordinate, mod((static_cast<int>(direction)) + directionOffset, ADJACENT_HEX_DIRECTIONS));

	//Check if direction topmost piece is taller (or as tall) as the source piece!
	while (currentNode != nullptr && currentNode->getGamePiece() != nullptr)
	{
		currentCoordinate->incrementZ();
		currentNode = getAdjacentHexNode(currentCoordinate, mod((static_cast<int>(direction)) + directionOffset, ADJACENT_HEX_DIRECTIONS));
	}

	if ((currentNode->getCoordinate()->getZ() < node->getCoordinate()->getZ()) || (currentCoordinate->getZ() == 0 && currentNode->getGamePiece() == nullptr))
	{
		delete currentCoordinate;
		return true;
	}

	delete currentCoordinate;
	return false;
}
