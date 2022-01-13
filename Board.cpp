#include "Board.h"

Board::Board() {
	_root = new HexNode();
	_gamePieces = new std::map<std::string, HexNode*>();
	_gamePieces->insert(std::pair<std::string, HexNode*>(_root->getCoordinate()->toString(), _root));
	_gamePieceStrategy = new PlacementStrategy(this);
}

bool Board::handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	return _gamePieceStrategy->handleGamePiece(gamePiece, coordinate);
}

void Board::setAdjacentSpots(HexNode* target) {
	_gamePieceStrategy->setAdjacentSpots(target);
}

std::vector<Coordinate*>* Board::getPlacementCandidates(HexNode* start, Player* player) {
	return _gamePieceStrategy->getCandidates(start, player);
}

std::map<std::string, HexNode*>* Board::getGamePieces() {
	return _gamePieces;
}

HexNode* Board::getRoot() {
	return _root;
}