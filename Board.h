#ifndef BOARD
#define BOARD

#include "HexNode.h"

#include "HexDirectionEnum.h"

class Board
{
private:
	HexNode* _root;

public:
	Board();
	void placeGamePiece(GamePiece* gamePiece);
	HexNode getRoot();
};

#endif