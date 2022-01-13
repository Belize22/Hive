#include "GamePiece.h"

GamePiece::GamePiece(Board* board, Player* player) {
	_board = board;
	_player = player;
	_active = false;
	_buried = false;
};


Player* GamePiece::getPlayer() {
	return _player;
}
