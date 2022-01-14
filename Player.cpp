#include "Player.h"

Player::Player(Board* board) {
	_board = board;
	_gamePieces = new std::vector<GamePiece*>();
	_queenBee = new GamePiece(board, this, QUEEN_BEE);
	_beetles = new std::vector<GamePiece*>();
	_grasshoppers = new std::vector<GamePiece*>();
	_spiders = new std::vector<GamePiece*>();
	_soldierAnts = new std::vector<GamePiece*>();
	for (int i = 0; i < BEETLE_AMOUNT; i++)
	{
		_beetles->push_back(new GamePiece(board, this, BEETLE));
	}
	for (int i = 0; i < GRASSHOPPER_AMOUNT; i++)
	{
		_grasshoppers->push_back(new GamePiece(board, this, GRASSHOPPER));
	}
	for (int i = 0; i < SPIDER_AMOUNT; i++)
	{
		_spiders->push_back(new GamePiece(board, this, SPIDER));
	}
	for (int i = 0; i < SOLDIER_ANT_AMOUNT; i++)
	{
		_soldierAnts->push_back(new GamePiece(board, this, SOLDIER_ANT));
	}
}

std::vector<GamePiece*>* Player::getGamePieces() {
	return _gamePieces;
};

bool Player::placeGamePiece(Coordinate* coordinate, GamePieceType gamePieceType) {
	if (_gamePieces->size() == 0) {
		std::cout << "Cannot place anymore pieces!" << std::endl;
		return false;
	}

	GamePiece* selectedGamePiece = nullptr;

	//TO-DO: Duplicate code. Refactor various arrays into an array of arrays later on.
	if (gamePieceType == QUEEN_BEE)
	{
		if (_queenBee->getHexNode() == nullptr) {
			selectedGamePiece = _queenBee;
		}
		else {
			return false;
		}
	}
	else if (gamePieceType == BEETLE)
	{
		for (int i = 0; i < BEETLE_AMOUNT; i++) {
			if (_beetles->at(i)->getHexNode() == nullptr) {
				selectedGamePiece = _beetles->at(i);
				break;
			}
			else if (i == BEETLE_AMOUNT - 1) {
				return false;
			}
		}
	}
	else if (gamePieceType == GRASSHOPPER)
	{
		for (int i = 0; i < GRASSHOPPER_AMOUNT; i++) {
			if (_grasshoppers->at(i)->getHexNode() == nullptr) {
				selectedGamePiece = _grasshoppers->at(i);
				break;
			}
			else if (i == GRASSHOPPER_AMOUNT - 1) {
				return false;
			}
		}
	}
	else if (gamePieceType == SPIDER)
	{
		for (int i = 0; i < SPIDER_AMOUNT; i++) {
			if (_spiders->at(i)->getHexNode() == nullptr) {
				selectedGamePiece = _spiders->at(i);
				break;
			}
			else if (i == SPIDER_AMOUNT - 1) {
				return false;
			}
		}
	}
	else //Soldier Ant
	{
		for (int i = 0; i < SOLDIER_ANT_AMOUNT; i++) {
			if (_soldierAnts->at(i)->getHexNode() == nullptr) {
				selectedGamePiece = _soldierAnts->at(i);
				break;
			}
			else if (i == SOLDIER_ANT_AMOUNT - 1) {
				return false;
			}
		}
	}

	if (selectedGamePiece == nullptr) {
		return false;
	}

	bool isValidSpot = _board->handleGamePiece(_gamePieces->at(0), coordinate);
	if (isValidSpot) {
		(_gamePieces->erase(_gamePieces->begin()));
	}
	return isValidSpot;
}