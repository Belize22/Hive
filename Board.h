#pragma once
#ifndef BOARD
#define BOARD

#include "HexNode.h"

class Board
{
private:
	HexNode* _root;

public:
	Board();
	void placePiece();
	HexNode getRoot();
};

#endif