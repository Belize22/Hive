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
	GamePiece* secondGamePiece = (currentPlayer->getGamePieces())->at(1);
	std::vector<Coordinate*>* coordinates = board->getPlacementCandidates(board->getRoot());
	currentPlayer->placeGamePiece(currentGamePiece, new Coordinate(new int(0), new int(0), new int(0)));
	currentPlayer->placeGamePiece(secondGamePiece, new Coordinate(new int(0), new int(-1), new int(0)));
	HexNode* root = board->getRoot();
	Coordinate* rootCoordinate = root->getCoordinate();
	std::cout << rootCoordinate->getX() << ", " << rootCoordinate->getY() << ", " << rootCoordinate->getZ() << std::endl;
	coordinates = board->getPlacementCandidates(board->getRoot());
	return 0;
}