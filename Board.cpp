#include "Board.h"

Board::Board() {
	placePiece();
}

void Board::placePiece() {
	_root = new HexNode();
}

HexNode Board::getRoot() {
	return *_root;
}
