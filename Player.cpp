#include "Player.h"

Player::Player(Board* board) {
	_board = board;
	for (int i = 0; i < 11; i++) {
		_gamePieces.push_back(new GamePiece(board, this));
	}
}