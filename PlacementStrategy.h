#ifndef PLACEMENT_STRATEGY
#define PLACEMENT_STRATEGY

class Board;
#include "GamePieceStrategy.h"
#include "GamePiece.h"
#include "Coordinate.h"

const int PLACEMENTS_BEFORE_MANDATORY_QUEEN_BEE_PLACEMENT = 3;

class PlacementStrategy : public GamePieceStrategy {
	public:
		PlacementStrategy();
		PlacementStrategy(Board* board);
		bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate);
		std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player);
};
#endif