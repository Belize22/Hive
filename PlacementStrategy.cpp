#include "PlacementStrategy.h"
#include "Board.h"

PlacementStrategy::PlacementStrategy() {

}

PlacementStrategy::PlacementStrategy(Board* board) {
	_board = board;
}

bool PlacementStrategy::handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate)
{
	HexNode* target = (_board->getGamePieces()->count(coordinate->toString()) > 0 ? 
		_board->getGamePieces()->at(coordinate->toString()) : nullptr);
	if (!pieceCanBePlaced(target) || spotAdjacentToOpposingPiece(gamePiece->getPlayer(), target->getCoordinate())) {
		if (target == nullptr) {
			std::cout << "Spot is not adjacent to the Hive!" << std::endl;
		}
		else if (target->getGamePiece() != nullptr) {
			std::cout << "Spot is occupied!" << std::endl;
		}
		else if (spotAdjacentToOpposingPiece(gamePiece->getPlayer(), target->getCoordinate())) {
			std::cout << "Cannot place piece next to opponent's!" << std::endl;
		}
		return false;
	}
	else {
		gamePiece->setHexNode(target);
		target->setGamePiece(gamePiece);
		setAdjacentSpots(target);
		return true;
	}

}