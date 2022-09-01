#include "Board.h"

Board::Board() {
	_mostRecentSpot = new HexNode(); //The first ever hex node made available (Player 1's first piece will always go here).
	_hexNodes = new std::map<std::string, HexNode*>();
	_hexNodes->insert(std::pair<std::string, HexNode*>(_mostRecentSpot->getCoordinate()->toString(), _mostRecentSpot));
	_placementStrategy = new PlacementStrategy(this);
	_queenBeeMovementStrategy = new QueenBeeMovementStrategy(this);
	_beetleMovementStrategy = new BeetleMovementStrategy(this);
	_grasshopperMovementStrategy = new GrasshopperMovementStrategy(this);
	_spiderMovementStrategy = new SpiderMovementStrategy(this);
	_soldierAntMovementStrategy = new SoldierAntMovementStrategy(this);
	_gamePieceStrategy = _placementStrategy; //Can only place pieces first turn
}

Board::~Board() {
	//Do not delete mostRecentSpot since it is part of gamePieces map!
	std::map<std::string, HexNode*>::iterator it = _hexNodes->begin();
	while (it != _hexNodes->end()) {
		delete it->second;
	}
	_hexNodes->clear();

	delete _placementStrategy;
	delete _queenBeeMovementStrategy;
	delete _beetleMovementStrategy;
	delete _grasshopperMovementStrategy;
	delete _spiderMovementStrategy;
	delete _soldierAntMovementStrategy;
}

bool Board::handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	return _gamePieceStrategy->handleGamePiece(gamePiece, coordinate);
}

bool Board::placeGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	_gamePieceStrategy = _placementStrategy;
	bool isValidPlacement = _gamePieceStrategy->handleGamePiece(gamePiece, coordinate);
	return isValidPlacement;
}

bool Board::moveGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	GamePieceType gamePieceType = gamePiece->getGamePieceType();
	if (gamePieceType == QUEEN_BEE) {
		_gamePieceStrategy = _queenBeeMovementStrategy;
	}
	else if (gamePieceType == BEETLE) {
		_gamePieceStrategy = _beetleMovementStrategy;
	}
	else if (gamePieceType == GRASSHOPPER) {
		_gamePieceStrategy = _grasshopperMovementStrategy;
	}
	else if (gamePieceType == SPIDER) {
		_gamePieceStrategy = _spiderMovementStrategy;
	}
	else if (gamePieceType == SOLDIER_ANT) {
		_gamePieceStrategy = _soldierAntMovementStrategy;
	}
	bool isValidPlacement = _gamePieceStrategy->handleGamePiece(gamePiece, coordinate);
	return isValidPlacement;
}

void Board::setAdjacentSpots(HexNode* target) {
	_gamePieceStrategy->setAdjacentSpots(target);
}

std::vector<Coordinate*>* Board::getPlacementCandidates(HexNode* start, Player* player) {
	return _gamePieceStrategy->getCandidates(start, player);
}

std::map<std::string, HexNode*>* Board::getHexNodes() {
	return _hexNodes;
}

bool Board::isGameOver(Player* playerOne, Player* playerTwo)
{
	bool playerOneQueenBeeSurrounded = _gamePieceStrategy->queenBeeSurrounded(playerOne->getGamePieces()->at(QUEEN_BEE)->at(0)->getHexNode());
	bool playerTwoQueenBeeSurrounded = _gamePieceStrategy->queenBeeSurrounded(playerTwo->getGamePieces()->at(QUEEN_BEE)->at(0)->getHexNode());

	if (playerOneQueenBeeSurrounded == playerTwoQueenBeeSurrounded) {
		if (playerOneQueenBeeSurrounded) {
			std::cout << "Game has ended in a stalemate!";
			return true;
		}

		return false;
	}

	int winnerId = playerOneQueenBeeSurrounded + 1;
	std::cout << "Player " << winnerId << " has won!" << std::endl;

	return true;
}

HexNode* Board::getMostRecentSpot() {
	return _mostRecentSpot;
}

void Board::setMostRecentSpot(HexNode* mostRecentSpot) {
	_mostRecentSpot = mostRecentSpot;
}
