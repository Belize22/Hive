#include "Board.h"

Board::Board() {
	_root = new HexNode();
	_gamePieces = new std::map<std::string, HexNode*>();
	_gamePieces->insert(std::pair<std::string, HexNode*>(_root->getCoordinate()->toString(), _root));
	_gamePieceStrategy = new PlacementStrategy(this);
}

bool Board::placeGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	HexNode* target = (_gamePieces->find(coordinate->toString()) != _gamePieces->end()) ? _gamePieces->at(coordinate->toString()) : nullptr;
	if (!pieceCanBePlaced(target) || spotAdjacentToOpposingPiece(gamePiece->getPlayer(), target->getCoordinate())) {
		if (target == nullptr) {
			std::cout << "Spot is not adjacent to the Hive!" << std::endl;
		}
		else if (target->getGamePiece() != nullptr) {
			std::cout << "Spot is occupied!" << std::endl;
		}
		else if (spotAdjacentToOpposingPiece(gamePiece->getPlayer(), target->getCoordinate())) {
			std::cout << "Cannot place piece next to opponent's!" << std::endl;
		}
		return false;
	}
	else {
		target->setGamePiece(gamePiece);
		setAdjacentSpots(target);
		return true;
	}
}

void Board::setAdjacentSpots(HexNode* target) {
	HexNode* currentNode;
	Coordinate* currentCoordinate = target->getCoordinate();
	for (int i = 0; i < 6; i++) {
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(i));
		currentNode = (_gamePieces->find(currentCoordinate->toString()) != _gamePieces->end()) ? _gamePieces->at(currentCoordinate->toString()) : nullptr;
		if (currentNode == nullptr) {
			_gamePieces->insert(std::pair<std::string, HexNode*>(currentCoordinate->toString(), new HexNode(new Coordinate(*currentCoordinate), static_cast<HexDirection>(i))));
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
}

std::vector<Coordinate*>* Board::getPlacementCandidates(HexNode* start, Player* player) {
	std::vector<HexNode*>* openList = new std::vector<HexNode*>();
	std::vector<HexNode*>* closedList = new std::vector<HexNode*>();
	std::vector<Coordinate*>* freeSpots = new std::vector<Coordinate*>();
	openList->push_back(start);
	while (openList->size() > 0) {
		HexNode* currentHexNode = openList->at(0);
		if (!currentHexNode->getGamePiece() && !spotAdjacentToOpposingPiece(player, currentHexNode->getCoordinate())) {
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
	HexNode* currentNode;
	Coordinate* currentCoordinate = currentHexNode->getCoordinate();
	openList->erase(openList->begin());
	for (int i = 0; i < 6; i++) {
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(i));
		currentNode = (_gamePieces->find(currentCoordinate->toString()) != _gamePieces->end()) ? _gamePieces->at(currentCoordinate->toString()) : nullptr;
		if (isAPlacementCandidate(openList, closedList, currentNode) && currentNode != nullptr) {
			openList->push_back(currentNode);
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
	closedList->push_back(currentHexNode);
}

std::map<std::string, HexNode*>* Board::getGamePieces() {
	return _gamePieces;
}

HexNode* Board::getRoot() {
	return _root;
}

bool Board::spotAdjacentToOpposingPiece(Player* player, Coordinate* coordinate) {
	if (onlyOnePiecePlaced()) {
		return false;
	}
	HexNode* currentNode;
	for (int i = 0; i < 6; i++) {
		coordinate->offsetCoordinate(coordinate, static_cast<HexDirection>(i));
		currentNode = (_gamePieces->find(coordinate->toString()) != _gamePieces->end()) ? _gamePieces->at(coordinate->toString()) : nullptr;
		if (currentNode != nullptr && currentNode->getGamePiece() != nullptr && currentNode->getGamePiece()->getPlayer() != player) {
			coordinate->offsetCoordinate(coordinate, static_cast<HexDirection>(mod(i + 3, 6)));
			return true;
		}
		coordinate->offsetCoordinate(coordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
	return false;
}

bool Board::onlyOnePiecePlaced() {
	HexNode* currentNode = _root;
	Coordinate* currentCoordinate = currentNode->getCoordinate();
	for (int i = 0; i < 6; i++) {
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(i));
		currentNode = (_gamePieces->find(currentCoordinate->toString()) != _gamePieces->end()) ? _gamePieces->at(currentCoordinate->toString()) : nullptr;
		if (currentNode != nullptr && currentNode->getGamePiece() != nullptr) {
			return false;
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
	return true;
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

//% is remainder, not mod in C++
int Board::mod(int a, int b) {
	return (a % b + b) % b;
}