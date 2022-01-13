#include "Player.h"

Player::Player(Board* board) {
	_board = board;
	_gamePieces = new std::vector<GamePiece*>();
	for (int i = 0; i < 11; i++) {
		_gamePieces->push_back(new GamePiece(board, this));
	}
}

std::vector<GamePiece*>* Player::getGamePieces() {
	return _gamePieces;
};

bool Player::placeGamePiece(Coordinate* coordinate) {
	if (_gamePieces->size() == 0) {
		std::cout << "Cannot place anymore pieces!" << std::endl;
		return false;
	}
	bool isValidSpot = _board->handleGamePiece(_gamePieces->at(0), coordinate);
	if (isValidSpot) {
		(_gamePieces->erase(_gamePieces->begin()));
	}
	return isValidSpot;
}