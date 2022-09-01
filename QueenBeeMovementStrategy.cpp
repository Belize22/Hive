#include "QueenBeeMovementStrategy.h"
#include "Board.h"

QueenBeeMovementStrategy::QueenBeeMovementStrategy() {

}

QueenBeeMovementStrategy::QueenBeeMovementStrategy(Board* board) {
	_board = board;
}

bool QueenBeeMovementStrategy::pieceCanMoveOnOccupiedSpace(HexNode* target) {
	std::cout << "Destination spot is occupied!" << std::endl;
	return false; //Only Beetle can move onto an occupied space!
}

bool QueenBeeMovementStrategy::isMovementProper(HexNode* source, Coordinate& destinationCoordinate) {
	HexNode* destination = (_board->getHexNodes()->find((&destinationCoordinate)->toString()) != _board->getHexNodes()->end()) ?
		(_board->getHexNodes()->at((&destinationCoordinate)->toString())) : nullptr;
	int direction = directionOfAdjacentDestination(source, destination);

	if (!areSourceAndDestinationAdjacent(source, destination, direction)) {
		std::cout << "Queen Bee cannot move more than 1 space!" << std::endl;
		return false;
	}

	//Only need to check one direction since source and destination are guaranteed to be z = 0.
	if (!FTMRespectedForSpecifiedDirection(source, static_cast<HexDirection>(direction))) {
		std::cout << "Moving that direction violates Freedom To Move rule!" << std::endl;
		return false;
	}

	return true;
}
