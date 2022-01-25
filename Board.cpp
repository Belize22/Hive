#include "Board.h"

Board::Board() {
	_mostRecentSpot = new HexNode(); //In the sense that a piece is placed or moved there (or the one available spot during Player 1's turn on Turn 1).
	_gamePieces = new std::map<std::string, HexNode*>();
	_gamePieces->insert(std::pair<std::string, HexNode*>(_mostRecentSpot->getCoordinate()->toString(), _mostRecentSpot));
	_gamePieceStrategy = new PlacementStrategy(this); //Can only place pieces first turn
}

bool Board::handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	return _gamePieceStrategy->handleGamePiece(gamePiece, coordinate);
}

bool Board::placeGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	_gamePieceStrategy = new PlacementStrategy(this);
	bool isValidPlacement = _gamePieceStrategy->handleGamePiece(gamePiece, coordinate);
	return isValidPlacement;
}

bool Board::moveGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	_gamePieceStrategy = new MovementStrategy(this);
	bool isValidPlacement = _gamePieceStrategy->handleGamePiece(gamePiece, coordinate);
	return isValidPlacement;
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

HexNode* Board::getMostRecentSpot() {
	return _mostRecentSpot;
}

void Board::setMostRecentSpot(HexNode* mostRecentSpot) {
	_mostRecentSpot = mostRecentSpot;
}