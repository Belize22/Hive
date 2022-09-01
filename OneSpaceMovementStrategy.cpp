#include "OneSpaceMovementStrategy.h"
#include "Board.h"

OneSpaceMovementStrategy::OneSpaceMovementStrategy() {

}

OneSpaceMovementStrategy::OneSpaceMovementStrategy(Board* board) {
	_board = board;
}

int OneSpaceMovementStrategy::directionOfAdjacentDestination(HexNode* source, HexNode* destination) {
	HexNode* currentNode;
	Coordinate* currentCoordinate = source->getCoordinate();
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentNode = getAdjacentHexNode(currentCoordinate, i);
		if (currentNode == destination) {
			return i;
		}
	}

	return -1; //Destination isn't adjacent.
}

bool OneSpaceMovementStrategy::areSourceAndDestinationAdjacent(HexNode* source, HexNode* destination, int direction) {
	if (direction == -1) {
		return false;
	}

	return true;
}

bool OneSpaceMovementStrategy::FTMRespectedForSpecifiedDirection(HexNode* node, HexDirection direction) {
	if (isAdjacentDirectionShorter(node, direction, -1)) { //Left
		return true;
	}

	if (isAdjacentDirectionShorter(node, direction, 1)) { //Right
		return true;
	}

	return false; //Piece cannot move one direction if both its adjacent directions are taller (or as tall) than the node!
}

bool OneSpaceMovementStrategy::isAdjacentDirectionShorter(HexNode* node, HexDirection direction, int directionOffset) {
	Coordinate* currentCoordinate = new Coordinate(new int(node->getCoordinate()->getX()), new int(node->getCoordinate()->getY()), new int(0));
	HexNode* currentNode = getAdjacentHexNode(currentCoordinate, mod((static_cast<int>(direction)) + directionOffset, ADJACENT_HEX_DIRECTIONS));
	HexNode* previousNode = currentNode; //Incase z = 0.

	//Check if direction topmost piece is taller (or as tall) as the source piece!
	while (currentNode != nullptr && currentNode->getGamePiece() != nullptr) {
		currentCoordinate->incrementZ();
		previousNode = currentNode;
		currentNode = getAdjacentHexNode(currentCoordinate, mod((static_cast<int>(direction)) + directionOffset, ADJACENT_HEX_DIRECTIONS));
	}

	//Compare to current node if z = 0 & not occupied since the node will never change.
	//(must use previous node as reference for z > 0 since availability only indicated for z = 0)
	//Ignore check entirely if adjacent node is not occupied.
	if ((previousNode->getCoordinate()->getZ() < node->getCoordinate()->getZ()) || 
		(previousNode->getCoordinate()->getZ() == 0 && previousNode->getGamePiece() == nullptr)) {
		delete currentCoordinate;
		return true;
	}

	delete currentCoordinate;
	return false;
}
