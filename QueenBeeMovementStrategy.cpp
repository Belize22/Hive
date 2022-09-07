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

std::vector<Coordinate*>* QueenBeeMovementStrategy::getCandidates(HexNode* start, Player* player) {
	std::vector<Coordinate*>* candidates = new std::vector<Coordinate*>();
	HexNode* currentNode;
	HexNode* adjacentNode;

	if (!canMovePiece(start, player)) {
		return candidates;
	}

	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		if (!FTMRespectedForSpecifiedDirection(start, static_cast<HexDirection>(i))) {
			continue;
		}

		currentNode = getAdjacentHexNode(start->getCoordinate(), i);

		if (currentNode->getGamePiece() != nullptr) {
			continue;
		}

		for (int j = 0; j < ADJACENT_HEX_DIRECTIONS; j++) { //Check that move doesn't violate OHR after it's complete.
			adjacentNode = getAdjacentHexNode(currentNode->getCoordinate(), j);
			if (adjacentNode != nullptr && adjacentNode->getGamePiece() != nullptr && adjacentNode != start) {
				break; //Found adjacent game piece that isn't a movement candidate!
			}
		}

		//OHR check here incase above loop does not find an adjacent game piece that isn't a movement candidate!
		if (adjacentNode != nullptr && adjacentNode->getGamePiece() != nullptr && adjacentNode != start) {
			candidates->push_back(currentNode->getCoordinate());
		}
	}

	return candidates;
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
