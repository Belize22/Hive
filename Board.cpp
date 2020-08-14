#include "Board.h"

Board::Board() {
	_root = new HexNode();
}

bool Board::placeGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	HexNode* target = getChosenPlacementCandidate(_root, coordinate);
	if (!pieceCanBePlaced(target) || spotAdjacentToOpposingPiece(gamePiece->getPlayer(), target)) {
		if (target == nullptr) {
			std::cout << "Spot is not adjacent to the Hive!" << std::endl;
		}
		else if (target->getGamePiece() != nullptr) {
			std::cout << "Spot is occupied!" << std::endl;
		}
		else if (spotAdjacentToOpposingPiece(gamePiece->getPlayer(), target)) {
			std::cout << "Cannot place piece next to opponent's!" << std::endl;
		}
		return false;
	}
	else {
		target->setGamePiece(gamePiece);
		return true;
	}
}

std::vector<Coordinate*>* Board::getPlacementCandidates(HexNode* start, Player* player) {
	std::vector<HexNode*>* openList = new std::vector<HexNode*>();
	std::vector<HexNode*>* closedList = new std::vector<HexNode*>();
	std::vector<Coordinate*>* freeSpots = new std::vector<Coordinate*>();
	openList->push_back(start);
	while (openList->size() > 0) {
		HexNode* currentHexNode = openList->at(0);
		if (!currentHexNode->getGamePiece() && !spotAdjacentToOpposingPiece(player, currentHexNode)) {
			freeSpots->push_back(currentHexNode->getCoordinate());
		}
		advanceBFS(openList, closedList);
	}
	delete openList;
	delete closedList;
	return freeSpots;
}


HexNode* Board::getChosenPlacementCandidate(HexNode* start, Coordinate* coordinate) {
	std::vector<HexNode*>* openList = new std::vector<HexNode*>();
	std::vector<HexNode*>* closedList = new std::vector<HexNode*>();
	openList->push_back(start);
	while (openList->size() > 0) {
		HexNode* currentHexNode = openList->at(0);
		if (*(currentHexNode->getCoordinate()) == *coordinate) {
			return currentHexNode;
		}
		advanceBFS(openList, closedList);
	}
	delete openList;
	delete closedList;
	return nullptr;
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

bool Board::spotAdjacentToOpposingPiece(Player* player, HexNode* spot) {
	//Exception: Second player placing first piece (must be adjacent to opponent's first piece)
	bool rootHasNoAdjacentPieces = true;
	for (int i = 0; i < _root->getAdjacentNodes()->size(); i++) {
		if (_root->getAdjacentNodes()->at(i) != nullptr && _root->getAdjacentNodes()->at(i)->getGamePiece() != nullptr) {
			rootHasNoAdjacentPieces = false;
		}
	}
	if (rootHasNoAdjacentPieces) {
		return false;
	}
	for (int i = 0; i < spot->getAdjacentNodes()->size(); i++) {
		if (spot->getAdjacentNodes()->at(i) != nullptr && spot->getAdjacentNodes()->at(i)->getGamePiece() != nullptr && spot->getAdjacentNodes()->at(i)->getGamePiece()->getPlayer() != player) {
			return true;
		}
	}
	return false;
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

bool Board::pieceCanBePlaced(HexNode* target) {
	return target != nullptr && target->getGamePiece() == nullptr;
}

