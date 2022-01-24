#include "MovementStrategy.h"
#include "Board.h"

MovementStrategy::MovementStrategy() {

}

MovementStrategy::MovementStrategy(Board* board) {
	_board = board;
}

bool MovementStrategy::handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate)
{
	//TO-DO: Get source hex node of game piece.
	HexNode* target = (_board->getGamePieces()->find(coordinate->toString()) !=
		_board->getGamePieces()->end()) ?
		_board->getGamePieces()->at(coordinate->toString()) : nullptr;
	if (!pieceCanBePlaced(target)) {
		if (target == nullptr) {
			std::cout << "Destination spot is not adjacent to the Hive!" << std::endl;
		}
		//Note: Beetle pieces can break this rule!
		else if (target->getGamePiece() != nullptr) {
			std::cout << "Destination spot is occupied!" << std::endl;
		}

		//TO-DO: Check if move respects One-Hive Rule

		//TO-DO: Check if move respects Freedom to Move Rule

		return false;
	}
	else {
		target->setGamePiece(gamePiece);
		setAdjacentSpots(target);
		return true;
	}
}

std::vector<Coordinate*>* MovementStrategy::getCandidates(HexNode* start, Player* player)
{
	return new std::vector<Coordinate*>(); //Placeholder
}