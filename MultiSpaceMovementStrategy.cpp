#include "MultiSpaceMovementStrategy.h"
#include "Board.h"

MultiSpaceMovementStrategy::MultiSpaceMovementStrategy() {
	maxDistance = INT_MAX;
}

MultiSpaceMovementStrategy::MultiSpaceMovementStrategy(Board* board) {
	_board = board;
	maxDistance = INT_MAX;
}

bool MultiSpaceMovementStrategy::isMovementProper(HexNode* source, Coordinate& destinationCoordinate) {
	HexNode* destination = (_board->getGamePieces()->find((&destinationCoordinate)->toString()) != _board->getGamePieces()->end()) ?
		(_board->getGamePieces()->at((&destinationCoordinate)->toString())) : nullptr;
	return destinationReachableByDFS(source, destination);
}

bool MultiSpaceMovementStrategy::pieceCanMoveOnOccupiedSpace(HexNode* target) {
	std::cout << "Destination spot is occupied!" << std::endl;
	return false; //Only Beetle can move onto an occupied space (this class is for Spider and Soldier Ant)!
}



//Since Spider cannot move without separating from an adjacent game piece and have it count as 1 move.
//(Soldier Ant "bypasses" this rule by having no limit on distance travelled!)
bool MultiSpaceMovementStrategy::traversingOnEdge(HexNode* node, HexDirection direction, HexNode* source) {
	Coordinate* currentCoordinate = new Coordinate(new int(node->getCoordinate()->getX()), new int(node->getCoordinate()->getY()), new int(0));
	HexNode* leftNode = getAdjacentHexNode(node->getCoordinate(), mod((static_cast<int>(direction)) - 1, ADJACENT_HEX_DIRECTIONS));
	HexNode* rightNode = getAdjacentHexNode(node->getCoordinate(), mod((static_cast<int>(direction)) + 1, ADJACENT_HEX_DIRECTIONS));

	delete currentCoordinate;

	//Easier to check FTM here than in the other FTM verification function since
	//source has to be considered "not occupied" in order to search properly.
	//XOR both enforces FTM and ensures that piece is travelling on edge.
	if ((spotIsOccupied(leftNode, source) != spotIsOccupied(rightNode, source))) {
		return true;
	}

	return false;
}

bool MultiSpaceMovementStrategy::destinationReachableByDFS(HexNode* source, HexNode* destination) {
	std::vector<HexNode*>* openList = new std::vector<HexNode*>();
	std::vector<int*>* openListDistances = new std::vector<int*>();
	std::vector<HexNode*>* closedList = new std::vector<HexNode*>();
	Coordinate* currentCoordinate = source->getCoordinate();
	HexNode* currentNode;
	bool foundOccupiedHexNode = false;

	openList->push_back(source);
	openListDistances->push_back(new int(0));

	while (openList->size() > 0 && openList->at(0) != destination) {
		HexNode* currentHexNode = openList->at(0);
		advanceBFSMultiMove(openList, openListDistances, closedList, source);
	}

	if (openList->size() > 0 && openList->at(0) == destination) { //Reached destination
		//e.g. Still not reachable if Spider travel 2 spaces to get to destination.
		bool satisfiedDistanceCondition = (distanceConditionSatisfied(openListDistances->at(0)));

		openList->clear();
		openListDistances->clear();
		closedList->clear();

		delete openList;
		delete openListDistances;
		delete closedList;

		if (!satisfiedDistanceCondition) {
			std::cout << "Piece not permitted to move that amount of spaces!" << std::endl;
		}

		return satisfiedDistanceCondition;
	}

	openList->clear();
	openListDistances->clear();
	closedList->clear();

	delete openList;
	delete openListDistances;
	delete closedList;

	std::cout << "Destination is either too far or inaccessible without violating Freedom to Move!" << std::endl;
	return false; //Cannot reach destination
}

void MultiSpaceMovementStrategy::advanceBFSMultiMove(std::vector<HexNode*>* openList, std::vector<int*>* openListDistances, std::vector<HexNode*>* closedList, HexNode* source) {
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
	}
}

bool MultiSpaceMovementStrategy::spotIsOccupied(HexNode* node, HexNode* source) {
	if (node == nullptr) {
		return false;
	}

	return (node->getGamePiece() != nullptr && node != source);
}