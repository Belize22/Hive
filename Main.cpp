#include <iostream>

#include "Board.h"

int main() {
	int turn = 1;
	Board * board = new Board();
	HexNode * root = &(board->getRoot());
	Coordinate rootCoordinate = root->getCoordinate();
	std::cout << rootCoordinate.getZ() << std::endl;
	return 0;
}