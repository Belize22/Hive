#include "BeetleMovementStrategy.h"
#include "Board.h"

BeetleMovementStrategy::BeetleMovementStrategy() {

}

BeetleMovementStrategy::BeetleMovementStrategy(Board* board) {
	_board = board;
}

bool BeetleMovementStrategy::pieceCanMoveOnOccupiedSpace(HexNode* target) {
	return true; //Only Beetle can move onto an occupied space!
}

std::vector<Coordinate*>* BeetleMovementStrategy::getCandidates(HexNode* start, Player* player) {
	std::vector<Coordinate*>* candidates = new std::vector<Coordinate*>();
	HexNode* currentNode;
	HexNode* adjacentNode;

	if (!canMovePiece(start, player)) {
		return candidates;
	}

	Coordinate* modifiedCoordinate = new Coordinate(
		new int(start->getCoordinate()->getX()),
		new int(start->getCoordinate()->getY()),
		new int (0)
	);

	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentNode = getAdjacentHexNode(modifiedCoordinate, i);
		changeToLowestZValueOfAvailableDestinationCoordinate(currentNode, *currentNode->getCoordinate());
		if (!FTMRespectedForSpecifiedDirection(start, static_cast<HexDirection>(i))
			&& !FTMRespectedForSpecifiedDirection(currentNode, static_cast<HexDirection>(mod(i + 3, ADJACENT_HEX_DIRECTIONS)))) {
			continue;
		}

		if (currentNode != nullptr && currentNode->getGamePiece() != nullptr) { //Skip OHR check if z-value of coordinate of movement candidate is greater than zero.
			candidates->push_back(currentNode->getCoordinate());
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

	delete modifiedCoordinate;
	return candidates;
}

bool BeetleMovementStrategy::isMovementProper(HexNode* source, Coordinate& destinationCoordinate)
{
	HexNode* destination = (_board->getHexNodes()->find((&destinationCoordinate)->toString()) != _board->getHexNodes()->end()) ?
		(_board->getHexNodes()->at((&destinationCoordinate)->toString())) : nullptr;

	int direction = directionOfAdjacentDestination(getLowestGamePieceForSource(source), destination);

	if (!areSourceAndDestinationAdjacent(source, destination, direction)) {
		std::cout << "Beetle cannot move more than 1 space!" << std::endl;
		return false;
	}

	HexNode* candidateDestination = changeToLowestZValueOfAvailableDestinationCoordinate(destination, destinationCoordinate);

	//Need to check both directions to account for multiple height possibilities of source, destination, and adjacent spots.
	if (!FTMRespectedForSpecifiedDirection(source, static_cast<HexDirection>(direction)) 
		&& !FTMRespectedForSpecifiedDirection(candidateDestination, static_cast<HexDirection>(mod(direction + 3, ADJACENT_HEX_DIRECTIONS)))) {
		std::cout << "Moving that direction violates Freedom To Move rule!" << std::endl;
		return false;
	}

	//Insert only when FTM is confirmed to be respected!
	//No issue if z = 0 since map insert does not replace upon discovery of existence!
	_board->getHexNodes()->insert(std::pair<std::string, HexNode*>((&destinationCoordinate)->toString(), candidateDestination));

	return true;
}

//If z > 0 for source, get equivalent where z = 0.
HexNode* BeetleMovementStrategy::getLowestGamePieceForSource(HexNode* source) {
	if (source->getCoordinate()->getZ() == 0) { //Measure to avoid creation and deletion of coordinate below. Not needed if z = 0.
		return source;
	}

	Coordinate* modifiedCoordinate = new Coordinate(
		new int(source->getCoordinate()->getX()),
		new int(source->getCoordinate()->getY()),
		new int(0)
	);

	HexNode* modifiedSource = (_board->getHexNodes()->find((modifiedCoordinate)->toString()) !=
		_board->getHexNodes()->end()) ?
		(_board->getHexNodes()->at((modifiedCoordinate)->toString())) : nullptr;

	delete modifiedCoordinate;
	return modifiedSource;
}

HexNode* BeetleMovementStrategy::changeToLowestZValueOfAvailableDestinationCoordinate(HexNode* destination, Coordinate& destinationCoordinate) {
	//Do not modify coordinate of spots below where the Beetle will go!
	Coordinate* candidateCoordinate = new Coordinate(new int(destination->getCoordinate()->getX()), new int(destination->getCoordinate()->getY()), new int(destination->getCoordinate()->getZ()));

	//Need to check for availability since z should be 0 if spot is available!
	while (spotExists(destination) && !spotIsAvailable(destination)) {
		candidateCoordinate->incrementZ();
		destination = (_board->getHexNodes()->find(candidateCoordinate->toString()) != _board->getHexNodes()->end()) ?
			_board->getHexNodes()->at(candidateCoordinate->toString()) : nullptr;
	}

	//Must change the coordinate, not the node (since prior node must still exist)
	destinationCoordinate = *candidateCoordinate;

	//Do not insert into board yet (move may not be done if FTM is violated)!
	return new HexNode(new Coordinate(*candidateCoordinate));
}
