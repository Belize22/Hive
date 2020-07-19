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
	currentPlayer->placeGamePiece(new Coordinate(new int(0), new int(0), new int(0)));	
	coordinates = board->getPlacementCandidates(board->getRoot());
	for (int i = 0; i < coordinates->size(); i++) {
		std::cout << coordinates->at(i)->getX() << ", " << coordinates->at(i)->getY() << ", " << coordinates->at(i)->getZ() << std::endl;
	}
	std::cout << "-----------------" << std::endl;
	currentPlayer->placeGamePiece(new Coordinate(new int(0), new int(-1), new int(0)));
	HexNode* root = board->getRoot();
	Coordinate* rootCoordinate = root->getCoordinate();
	coordinates = board->getPlacementCandidates(board->getRoot());
	for (int i = 0; i < coordinates->size(); i++) {
		std::cout << coordinates->at(i)->getX() << ", " << coordinates->at(i)->getY() << ", " << coordinates->at(i)->getZ() << std::endl;
	}
	std::cout << "-----------------" << std::endl;
	return 0;
}