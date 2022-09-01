#include "GrasshopperMovementStrategy.h"
#include "Board.h"

GrasshopperMovementStrategy::GrasshopperMovementStrategy() {

}

GrasshopperMovementStrategy::GrasshopperMovementStrategy(Board* board) {
	_board = board;
}

bool GrasshopperMovementStrategy::pieceCanMoveOnOccupiedSpace(HexNode* target) {
	std::cout << "Destination spot is occupied!" << std::endl;
	return false; //Only Beetle can move onto an occupied space!
}

bool GrasshopperMovementStrategy::isMovementProper(HexNode* source, Coordinate& destinationCoordinate) {
	HexNode* destination = (_board->getGamePieces()->find((&destinationCoordinate)->toString()) != _board->getGamePieces()->end()) ?
		(_board->getGamePieces()->at((&destinationCoordinate)->toString())) : nullptr;

	if (!sourceAndDestinationAreAligned(source, destination)) {
		std::cout << "Grasshopper is not permitted to hop at that angle!" << std::endl;
		return false;
	}

	HexDirection direction = getDirectionToDestination(source, destination);

	if (!nodesBetweenSourceAndDestinationAreOccupied(source, destination, direction)) {
		std::cout << "Grasshopper must hop over at least one occupied space without skipping an available space!" << std::endl;
		return false;
	}

	return true;
}



HexDirection GrasshopperMovementStrategy::getDirectionToDestination(HexNode* source, HexNode* destination) {
	if (source->getCoordinate()->getX() == destination->getCoordinate()->getX()) {
		return (source->getCoordinate()->getY() > destination->getCoordinate()->getY()) ? UP : DOWN;
	}
	else {
		if (source->getCoordinate()->getY() > destination->getCoordinate()->getY() ||
			(source->getCoordinate()->getY() == destination->getCoordinate()->getX() &&
			 source->getCoordinate()->getX() % 2 != 0)) {
			return (source->getCoordinate()->getX() > destination->getCoordinate()->getX()) ? UP_LEFT : UP_RIGHT;
		}
		else { //Covers (y1 < y2 || (y1 == y2 && x1 % 2 == 0), source is 1, destination is 2.
			return (source->getCoordinate()->getX() > destination->getCoordinate()->getX()) ? DOWN_LEFT : DOWN_RIGHT;
		}
	}
}

bool GrasshopperMovementStrategy::nodesBetweenSourceAndDestinationAreOccupied(HexNode* source, HexNode* destination, HexDirection direction) {
	HexNode* currentNode = getAdjacentHexNode(source->getCoordinate(), static_cast<int>(direction));
	if (currentNode == destination) {
		return false; //Source and Destination cannot be adjacent (must hop over at least one game piece).
	}

	while (currentNode != destination) {
		if (currentNode->getGamePiece() == nullptr) {
			return false; //Cannot make multiple hops in a single turn!
		}

		currentNode = getAdjacentHexNode(currentNode->getCoordinate(), static_cast<int>(direction));
	}

	return true;
}

bool GrasshopperMovementStrategy::sourceAndDestinationAreAligned(HexNode* source, HexNode* destination)
{
	int x1 = source->getCoordinate()->getX();
	int x2 = destination->getCoordinate()->getX();
	int y1 = source->getCoordinate()->getY();
	int y2 = destination->getCoordinate()->getY();

	if (source->getCoordinate()->getX() == destination->getCoordinate()->getX()) { //Are they vertically aligned?
		return true;
	}

	if (source->getCoordinate()->getY() > destination->getCoordinate()->getY() ||
	   (source->getCoordinate()->getY() == destination->getCoordinate()->getX() && 
		mod(source->getCoordinate()->getX(), 2) != 0)) {
		return verifyDiagonalAlignment(source, destination, -1);
	}
	else //Covers (y1 < y2 || (y1 == y2 && x1 % 2 == 0), source is 1, destination is 2.
	{
		return verifyDiagonalAlignment(source, destination, 1);
	}
}

bool GrasshopperMovementStrategy::verifyDiagonalAlignment(HexNode* source, HexNode* destination, int yOffset) {
	//Use copies of coordinates since algorithm will change these values!
	int* x1 = new int(source->getCoordinate()->getX());
	int* x2 = new int(destination->getCoordinate()->getX());
	int* y1 = new int(source->getCoordinate()->getY());
	int* y2 = new int(destination->getCoordinate()->getY());

	int* moduloOffset = new int ((int)sqrt(yOffset + 1)); //To ensure that it's equal to 0 for negative offset and 1 for positive offset.

	int* yN = y1;

	if ((*x1) > (*x2)) {
		while ((*x1) > *(x2)) {
			if (mod(*x1, 2) == *(moduloOffset)) {
				(*yN) += yOffset;
			}
			(*x1)--;
		}
	}
	else {
		while (*(x1) < *(x2)) {
			if (mod(*x1, 2) == *(moduloOffset)) {
				(*yN) += yOffset;
			}
			(*x1)++;
		}
	}

	delete moduloOffset;
	delete x1;
	delete x2;

	if ((*yN) != (*y2)) {
		delete y1;
		delete y2;
		return false;
	}

	delete y1;
	delete y2;
	return true;
}