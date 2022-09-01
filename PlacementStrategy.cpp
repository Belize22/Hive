#include "PlacementStrategy.h"
#include "Board.h"
#include "Player.h"

PlacementStrategy::PlacementStrategy() {

}

PlacementStrategy::PlacementStrategy(Board* board) {
	_board = board;
}

bool PlacementStrategy::handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate)
{
	HexNode* target = (_board->getGamePieces()->count(coordinate->toString()) > 0 ? 
		_board->getGamePieces()->at(coordinate->toString()) : nullptr);

	if (*(gamePiece->getPlayer()->getGamePieceQuantity()) >= PLACEMENTS_BEFORE_MANDATORY_QUEEN_BEE_PLACEMENT &&
		  gamePiece->getPlayer()->getGamePieces()->at(QUEEN_BEE)->at(0)->getHexNode() == nullptr &&
		  gamePiece->getGamePieceType() != QUEEN_BEE) {
		std::cout << "Must place Queen Bee this turn!" << std::endl;
		return false;
	}

	if (!pieceCanBePlaced(target) || spotAdjacentToOpposingPiece(gamePiece->getPlayer(), target->getCoordinate())) {
		if (!spotExists(target)) {
			std::cout << "Spot is not adjacent to the Hive!" << std::endl;
		}
		else if (!spotIsAvailable(target)) {
			std::cout << "Spot is occupied!" << std::endl;
		}
		else if (spotAdjacentToOpposingPiece(gamePiece->getPlayer(), target->getCoordinate())) {
			std::cout << "Cannot place piece next to opponent's!" << std::endl;
		}

		return false;
	}
	else {
		//Add spaces that are adjacent to the moved game piece after movement is completed!
		gamePiece->setHexNode(target);
		target->setGamePiece(gamePiece);
		setAdjacentSpots(target);
		_board->setMostRecentSpot(target);

		gamePiece->getPlayer()->incrementGamePieceQuantity();

		return true;
	}
}