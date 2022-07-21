#include "BeetleMovementStrategy.h"
#include "Board.h"

BeetleMovementStrategy::BeetleMovementStrategy() {

}

BeetleMovementStrategy::BeetleMovementStrategy(Board* board) {
	_board = board;
}

bool BeetleMovementStrategy::pieceCanMoveOnOccupiedSpace(HexNode* target)
{
	return true; //Only Beetle can move onto an occupied space!
}

bool BeetleMovementStrategy::isMovementProper(HexNode* source, HexNode* destination)
{
	std::cout << "Moving Beetle!" << std::endl;
	int direction = directionOfAdjacentDestination(source, destination);
	if (!areSourceAndDestinationAdjacent(source, destination, direction))
	{
		std::cout << "Beetle cannot move more than 1 space!" << std::endl;
		return false;
	}

	changeToLowestZValueOfAvailableDestinationCoordinate(destination);

	//Need to check both directions to account for multiple height possibilities of source, destination, and adjacent spots.
	if (!FTMRespectedForSpecifiedDirection(source, static_cast<HexDirection>(direction)) && 
		!FTMRespectedForSpecifiedDirection(destination, static_cast<HexDirection>(mod(direction + 3, ADJACENT_HEX_DIRECTIONS))))
	{
		std::cout << "Moving that direction violates Freedom To Move rule!" << std::endl;
		return false;
	}

	return true;
}

void BeetleMovementStrategy::changeToLowestZValueOfAvailableDestinationCoordinate(HexNode* destination)
{
	HexNode* currentNode = destination;

	//Do not modify coordinate of spots below where the Beetle will go!
	Coordinate* candidateCoordinate = new Coordinate(new int(destination->getCoordinate()->getX()), new int(destination->getCoordinate()->getY()), new int(destination->getCoordinate()->getZ()));

	//Need to check for availability since z should be 0 if spot is available!
	while (spotExists(currentNode) && !spotIsAvailable(currentNode))
	{
		candidateCoordinate->incrementZ();
		currentNode = (_board->getGamePieces()->find(candidateCoordinate->toString()) !=
			_board->getGamePieces()->end()) ?
			_board->getGamePieces()->at(candidateCoordinate->toString()) : nullptr;
	}

	destination = currentNode; //Change destination to available spot with lowest z-value!
}
