#include "Board.h"

Board::Board() {
	_root = new HexNode();
}

void Board::placeGamePiece(GamePiece* gamePiece) {
	_root->setGamePiece(gamePiece);
}

std::vector<Coordinate*>* Board::getPlacementCandidates(HexNode* start) {
	std::vector<HexNode*>* openList = new std::vector<HexNode*>();
	std::vector<HexNode*>* closedList = new std::vector<HexNode*>();
	std::vector<Coordinate*>* freeSpots = new std::vector<Coordinate*>();
	openList->push_back(start);
	while (openList->size() > 0) {
		HexNode* currentHexNode = openList->at(0);
		if (!currentHexNode->getGamePiece()) {
			freeSpots->push_back(currentHexNode->getCoordinate());
		}
		advanceBFS(openList, closedList);
	}
	delete openList;
	delete closedList;
	return freeSpots;
}

void Board::advanceBFS(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList) {
	HexNode* currentHexNode = openList->at(0);
	std::vector<HexNode*>* adjacentNodes = currentHexNode->getAdjacentNodes();
	openList->erase(openList->begin());
	for (size_t i = 0; i < adjacentNodes->size(); i++) {
		if (isAPlacementCandidate(openList, closedList, adjacentNodes->at(i)) && adjacentNodes->at(i)) {
			openList->push_back(adjacentNodes->at(i));
		}
	}
	closedList->push_back(currentHexNode);
}

HexNode* Board::getRoot() {
	return _root;
}

bool Board::isAPlacementCandidate(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList, HexNode* currentHexNode) {
	for (size_t i = 0; i < openList->size(); i++) {
		if (currentHexNode == openList->at(i)) {
			return false;
		}
	}	
	for (size_t i = 0; i < closedList->size(); i++) {
		if (currentHexNode == closedList->at(i)) {
			return false;
		}
	}
	return true;
}

