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

void Player::placeGamePiece(Coordinate* coordinate) {
	_board->placeGamePiece(_gamePieces->at(0), coordinate);
	(_gamePieces->erase(_gamePieces->begin()));
}