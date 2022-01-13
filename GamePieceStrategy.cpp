#include "GamePieceStrategy.h"
#include "Board.h"

GamePieceStrategy::GamePieceStrategy()
{

}

GamePieceStrategy::GamePieceStrategy(Board* board) {
	_board = board;
}

void GamePieceStrategy::setAdjacentSpots(HexNode* target) {
	HexNode* currentNode;
	Coordinate* currentCoordinate = target->getCoordinate();
	for (int i = 0; i < 6; i++) {
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(i));
		currentNode = (_board->getGamePieces()->find(currentCoordinate->toString()) != 
			_board->getGamePieces()->end()) ? 
			_board->getGamePieces()->at(currentCoordinate->toString()) : nullptr;
		if (currentNode == nullptr) {
			_board->getGamePieces()->insert(std::pair<std::string, HexNode*>(currentCoordinate->toString(), new HexNode(new Coordinate(*currentCoordinate), static_cast<HexDirection>(i))));
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
}

bool GamePieceStrategy::pieceCanBePlaced(HexNode* target) {
	return target != nullptr && target->getGamePiece() == nullptr;
}

//% is remainder, not mod in C++
int GamePieceStrategy::mod(int a, int b) {
	return (a % b + b) % b;
}