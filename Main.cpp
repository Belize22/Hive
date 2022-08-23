#include <iostream>
#include <vector>

#include "Board.h"
#include "Player.h"
#include "InputParser.h"
#include "GamePieceTypeEnum.h"
#include "GamePieceInteractionType.h"

const int NUM_PLAYERS = 2;

void displayPlacementCandidates(std::vector<Coordinate*>* coordinates); 
Player* changePlayer(std::vector<Player*>* players, int* currentPlayerNumber);
std::string getRegexInput();
int getCoordinateInput();
bool isGameOver(Board* board, Player* playerOne, Player* playerTwo);
bool canPassTurn(Player* currentPlayer, Board* board);

int main() {
	int turn = 1;
	Board* board = new Board();
	std::vector<Player*>* players = new std::vector<Player*>;
	for (int i = 0; i < NUM_PLAYERS; i++) {
		players->push_back(new Player(board, &i));
	}
	int* currentPlayerNumber = new int(-1);
	Player* currentPlayer = changePlayer(players, currentPlayerNumber);
	while (true) {
		displayPlacementCandidates(board->getPlacementCandidates(board->getMostRecentSpot(), currentPlayer));
		std::cout << "Place a piece: P[A|B|G|Q|S]([-]?[0-9]+,[-]?[0-9]+" << std::endl;
		std::cout << "Move a piece: M[A|B|G|Q|S][0-9]([-]?[0-9]+,[-]?[0-9]+" << std::endl;
		std::cout << "Insert Input: ";
		std::string input = getRegexInput();
		if (input == "PASS") {
			if (canPassTurn(currentPlayer, board)) {
				std::cout << "Passing Turn!" << std::endl;
				currentPlayer = changePlayer(players, currentPlayerNumber);
			}
			else {
				std::cout << "Can only pass turn if no viable placement options exist!" << std::endl;
			}
		}
		else if (input != "") {
			GamePieceInteractionType gamePieceInteractionType = InputParser::getGamePieceInteractionTypeFromInput(input);
			if (gamePieceInteractionType == PLACEMENT) {
				GamePieceType gamePieceType = InputParser::getGamePieceTypeFromInput(input);
				Coordinate* inputCoordinate = InputParser::getCoordinateFromInput(input);
				bool isValidSpot = currentPlayer->placeGamePiece(inputCoordinate, gamePieceType);
				delete inputCoordinate;
				if (isValidSpot) {
					if (isGameOver(board, players->at(0), players->at(1))) {
						break;
					}
					currentPlayer = changePlayer(players, currentPlayerNumber);
				}
			}
			else if (gamePieceInteractionType == MOVEMENT) {
				GamePiece* gamePiece = InputParser::getGamePieceFromInput(currentPlayer, input);
				Coordinate* inputCoordinate = InputParser::getCoordinateFromInput(input);
				bool isValidSpot = currentPlayer->moveGamePiece(inputCoordinate, gamePiece);
				delete inputCoordinate;
				if (isValidSpot) {
					if (isGameOver(board, players->at(0), players->at(1))) {
						break;
					}
					currentPlayer = changePlayer(players, currentPlayerNumber);
				}
			}
		}
	}
	return 0;
}

void displayPlacementCandidates(std::vector<Coordinate*>* coordinates) {
	if (coordinates == nullptr) {
		std::cout << "All game pieces have been placed!" << std::endl;
		return;
	}

	if (coordinates->size() == 0) {
		std::cout << "No possible placement candidates!" << std::endl;
		return;
	}

	std::cout << "Here are all placement candidates: " << std::endl;
	for (int i = 0; i < coordinates->size(); i++) {
    	std::cout << coordinates->at(i)->getX() << ", " << coordinates->at(i)->getY() << ", " << coordinates->at(i)->getZ() << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}

std::string getRegexInput() {
	std::string input;
	std::cin >> input;
	if (InputParser::isValidRegex(input)) {
		return input;
	}
	else {
		return "";
	}
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

bool isGameOver(Board* board, Player* playerOne, Player* playerTwo) {
	return board->isGameOver(playerOne, playerTwo);
}

bool canPassTurn(Player* currentPlayer, Board* board) {
	std::vector<Coordinate*>* placementCandidates = board->getPlacementCandidates(board->getMostRecentSpot(), currentPlayer);
	return (placementCandidates == nullptr || placementCandidates->size() == 0);
}
