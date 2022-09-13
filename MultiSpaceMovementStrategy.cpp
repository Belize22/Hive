#include "MultiSpaceMovementStrategy.h"
#include "Board.h"

MultiSpaceMovementStrategy::MultiSpaceMovementStrategy() {
	maxDistance = INT_MAX;
}

MultiSpaceMovementStrategy::MultiSpaceMovementStrategy(Board* board) {
	_board = board;
	maxDistance = INT_MAX;
}


std::vector<Coordinate*>* MultiSpaceMovementStrategy::getCandidates(HexNode* start, Player* player) {
	std::vector<Coordinate*>* candidates = new std::vector<Coordinate*>();

	if (!canMovePiece(start, player)) {
		return candidates;
	}

	candidates = performMultiMoveBFS(start, nullptr);
	return nullptr;
}

bool MultiSpaceMovementStrategy::isMovementProper(HexNode* source, Coordinate& destinationCoordinate) {
	HexNode* destination = (_board->getHexNodes()->find((&destinationCoordinate)->toString()) != _board->getHexNodes()->end()) ?
		(_board->getHexNodes()->at((&destinationCoordinate)->toString())) : nullptr;
	return destinationReachableByBFS(source, destination);
}

bool MultiSpaceMovementStrategy::pieceCanMoveOnOccupiedSpace(HexNode* target) {
	std::cout << "Destination spot is occupied!" << std::endl;
	return false; //Only Beetle can move onto an occupied space (this class is for Spider and Soldier Ant)!
}



//Since Spider cannot move without separating from an adjacent game piece and have it count as 1 move.
//(Soldier Ant "bypasses" this rule by having no limit on distance travelled!)
bool MultiSpaceMovementStrategy::traversingOnEdge(HexNode* node, HexDirection direction, HexNode* source) {
	HexNode* leftNode = getAdjacentHexNode(node->getCoordinate(), mod((static_cast<int>(direction)) - 1, ADJACENT_HEX_DIRECTIONS));
	HexNode* rightNode = getAdjacentHexNode(node->getCoordinate(), mod((static_cast<int>(direction)) + 1, ADJACENT_HEX_DIRECTIONS));

	//Easier to check FTM here than in the other FTM verification function since
	//source has to be considered "not occupied" in order to search properly.
	//XOR both enforces FTM and ensures that piece is travelling on edge.
	if ((spotIsOccupied(leftNode, source) != spotIsOccupied(rightNode, source))) {
		return true;
	}

	return false;
}

bool MultiSpaceMovementStrategy::destinationReachableByBFS(HexNode* source, HexNode* destination) {
	std::vector<Coordinate*>* candidates = performMultiMoveBFS(source, destination);

	if (candidates->size() > 0 && candidates->at(0) == destination->getCoordinate()) {
		return true;
	}

	return false;
}

std::vector<Coordinate*>* MultiSpaceMovementStrategy::performMultiMoveBFS(HexNode* source, HexNode* destination) {
	std::vector<Coordinate*>* candidates = new std::vector<Coordinate*>();

	std::vector<HexNode*>* openList = new std::vector<HexNode*>();
	std::vector<int*>* openListDistances = new std::vector<int*>();
	std::vector<HexNode*>* closedList = new std::vector<HexNode*>();
	std::vector<int*>* closedListDistances = new std::vector<int*>();

	Coordinate* currentCoordinate = source->getCoordinate();
	HexNode* currentNode;
	bool foundOccupiedHexNode = false;

	openList->push_back(source);
	openListDistances->push_back(new int(0));

	while (openList->size() > 0 && openList->at(0) != destination) {
		HexNode* currentHexNode = openList->at(0);
		advanceBFSMultiMove(openList, openListDistances, closedList, closedListDistances, source);
	}

	if (openList->size() > 0 && openList->at(0) == destination) { //Reached destination
		//e.g. Still not reachable if Spider travel 2 spaces to get to destination.
		bool satisfiedDistanceCondition = (distanceConditionSatisfied(openListDistances->at(0)));

		openList->clear();
		for (int i = 0; i < openListDistances->size(); i++) {
			delete openListDistances->at(i);
		}
		openListDistances->clear();
		closedList->clear();

		delete openList;
		delete openListDistances;
		delete closedList;

		if (!satisfiedDistanceCondition) {
			std::cout << "Piece not permitted to move that amount of spaces!" << std::endl;
		}

		if (satisfiedDistanceCondition) {
			candidates->push_back(destination->getCoordinate());
		}
		return candidates;
	}

	if (destination == nullptr) { //For finding all movement candidates.
		for (int i = 0; i < closedList->size(); i++) {
			if (distanceConditionSatisfied(closedListDistances->at(i))) {
				candidates->push_back(closedList->at(i)->getCoordinate());
			}
		}
	}

	openList->clear();
	for (int i = 0; i < openListDistances->size(); i++) {
		delete openListDistances->at(i);
	}
	openListDistances->clear();
	closedList->clear();

	delete openList;
	delete openListDistances;
	delete closedList;

	if (destination != nullptr) {
		std::cout << "Destination is either too far or inaccessible without violating Freedom to Move!" << std::endl;
	}

	return candidates; //Cannot reach destination (or finding movement candidates)
}

void MultiSpaceMovementStrategy::advanceBFSMultiMove(std::vector<HexNode*>* openList, std::vector<int*>* openListDistances, std::vector<HexNode*>* closedList, std::vector<int*>* closedListDistances, HexNode* source) {
	HexNode* currentHexNode = openList->at(0);
	HexNode* currentNode;
	int* nodeDistance = openListDistances->at(0);
	Coordinate* currentCoordinate = currentHexNode->getCoordinate();

	openList->erase(openList->begin());
	openListDistances->erase(openListDistances->begin());

	if ((*nodeDistance) >= maxDistance) { //Don't explore candidates beyond max distance the piece can travel!
		return;
	}

	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentNode = getAdjacentHexNode(currentCoordinate, i);
		if (currentNode != nullptr && currentNode->getGamePiece() == nullptr 
			&& traversingOnEdge(currentHexNode, static_cast<HexDirection>(i), source) 
			&& !std::count(closedList->begin(), closedList->end(), currentNode)) {
			openList->push_back(currentNode);
			int* newNodeDistance = new int((*nodeDistance) + 1);
			openListDistances->push_back(newNodeDistance);
		}
	}

	if (!std::count(closedList->begin(), closedList->end(), currentHexNode)) {
		closedList->push_back(currentHexNode);
		closedListDistances->push_back(nodeDistance);
	}
}

bool MultiSpaceMovementStrategy::spotIsOccupied(HexNode* node, HexNode* source) {
	if (node == nullptr) {
		return false;
	}

	return (node->getGamePiece() != nullptr && node != source);
}