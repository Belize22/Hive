#include <iostream>
#include <vector>

#include "Board.h"
#include "Player.h"

void displayPlacementCandidates(std::vector<Coordinate*>* coordinates); 
Player* changePlayer(std::vector<Player*>* players, int* currentPlayerNumber);
int getCoordinateInput();

int main() {
	int turn = 1;
	Board* board = new Board();
	std::vector<Player*>* players = new std::vector<Player*>;
	for (int i = 0; i < 2; i++) {
		players->push_back(new Player(board));
	}
	int* currentPlayerNumber = new int(-1);
	Player* currentPlayer = changePlayer(players, currentPlayerNumber);
	while (true) {
		displayPlacementCandidates(board->getPlacementCandidates(board->getRoot()));
		std::cout << "Insert x-coordinate: ";
		int x = getCoordinateInput();
		std::cout << "Insert y-coordinate: ";
		int y = getCoordinateInput();
		int z = 0;
		Coordinate* inputCoordinate = new Coordinate(&x, &y, &z);
		bool isValidSpot = currentPlayer->placeGamePiece(inputCoordinate);
		delete inputCoordinate;
		if (isValidSpot) {
			currentPlayer = changePlayer(players, currentPlayerNumber);
		}
	}
	return 0;
}

void displayPlacementCandidates(std::vector<Coordinate*>* coordinates) {
	std::cout << "Here are all placement candidates: " << std::endl;
	for (int i = 0; i < coordinates->size(); i++) {
    	std::cout << coordinates->at(i)->getX() << ", " << coordinates->at(i)->getY() << ", " << coordinates->at(i)->getZ() << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}

int getCoordinateInput() {
	int input;
	std::cin >> input;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Coordinate must be a number: ";
		std::cin >> input;
	}
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	return input;
}

Player* changePlayer(std::vector<Player*>* players, int* currentPlayerNumber) {
	*currentPlayerNumber = (*currentPlayerNumber + 1) % players->size();
	std::cout << "Player " << *currentPlayerNumber + 1 << "'s Turn!" << std::endl;
	return players->at(*currentPlayerNumber);
}