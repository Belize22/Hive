#include "Board.h"

Board::Board() {
	_root = new HexNode();
}

void Board::placeGamePiece(GamePiece* gamePiece) {
	_root->setGamePiece(gamePiece);
}

HexNode Board::getRoot() {
	return *_root;
}
