#include "GamePiece.h"

GamePiece::GamePiece(Board* board, Player* player, GamePieceType gamePieceType) {
	_board = board;
	_player = player;
	_gamePieceType = gamePieceType;
	_hexNode = nullptr;
	_active = false;
	_buried = false;
};


Player* GamePiece::getPlayer() {
	return _player;
}

HexNode* GamePiece::getHexNode() {
	return _hexNode;
}

GamePieceType GamePiece::getGamePieceType() {
	return _gamePieceType;
}

void GamePiece::setHexNode(HexNode* hexNode) {
	_hexNode = hexNode;
}
