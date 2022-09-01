#ifndef MOVEMENT_STRATEGY
#define MOVEMENT_STRATEGY

class Board;
#include "GamePieceStrategy.h"

class MovementStrategy : public GamePieceStrategy {
	private:
		void unsetAdjacentSpots(HexNode* target);
		bool queenBeePlaced(Player* player);
		bool isBuried(HexNode* source);
		bool destinationIsAdjacentToAnotherGamePiece(HexNode* source, Coordinate* destination);
		bool respectsOHR(GamePiece* gamePiece);
		bool surroundingGamePiecesAreDisjointed(GamePiece* gamePiece);
		bool hiveWillSeparateAfterMovingPiece(GamePiece* gamePiece);
		void advanceBFS(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList);

	public:
		MovementStrategy();
		MovementStrategy(Board* board);
		bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate);
		std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player);
		virtual bool pieceCanMoveOnOccupiedSpace(HexNode* target) = 0;
		virtual bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate) = 0;
};

#endif
