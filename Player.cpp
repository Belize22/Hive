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

void Player::placeGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	_board->placeGamePiece(gamePiece, coordinate);
}