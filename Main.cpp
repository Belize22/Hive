#include <iostream>
#include <vector>

#include "Board.h"
#include "Player.h"

int main() {
	int turn = 1;
	Board* board = new Board();
	std::vector<Player*> players;
	for (int i = 0; i < 2; i++) {
		players.push_back(new Player(board));
	}
	Player* currentPlayer = players.at(0);
	GamePiece* currentGamePiece = (currentPlayer->getGamePieces())->at(0);
	currentPlayer->placeGamePiece(currentGamePiece);
	HexNode* root = &(board->getRoot());
	Coordinate* rootCoordinate = root->getCoordinate();
	std::cout << rootCoordinate->getX() << ", " << rootCoordinate->getY() << ", " << rootCoordinate->getZ() << std::endl;
	return 0;
}