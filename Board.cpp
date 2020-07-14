#include "Board.h"

Board::Board() {
	placePiece();
}

void Board::placePiece() {
	_root = new HexNode();
	Coordinate* coordinate = &(_root->getCoordinate());
	_root = new HexNode(new Coordinate(*coordinate), UP);
}

HexNode Board::getRoot() {
	return *_root;
}
