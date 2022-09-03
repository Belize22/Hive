#ifndef QUEEN_BEE_MOVEMENT_STRATEGY
#define QUEEN_BEE_MOVEMENT_STRATEGY

class Board;
#include "OneSpaceMovementStrategy.h"

class QueenBeeMovementStrategy : public OneSpaceMovementStrategy {
	public:
		QueenBeeMovementStrategy();
		QueenBeeMovementStrategy(Board* board);
		bool pieceCanMoveOnOccupiedSpace(HexNode* target);
		std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player);
		bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate);
};

#endif