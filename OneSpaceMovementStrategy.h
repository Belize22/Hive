#ifndef ONE_SPACE_MOVEMENT_STRATEGY
#define ONE_SPACE_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class OneSpaceMovementStrategy : public MovementStrategy {
    private:
		bool isAdjacentDirectionShorter(HexNode* node, HexDirection direction, int directionOffset);

	protected:
		int directionOfAdjacentDestination(HexNode* source, HexNode* destination);
		bool FTMRespectedForSpecifiedDirection(HexNode* source, HexDirection direction);
		bool areSourceAndDestinationAdjacent(HexNode* source, HexNode* destination, int direction);

	public:
		OneSpaceMovementStrategy();
		OneSpaceMovementStrategy(Board* board);
		virtual bool pieceCanMoveOnOccupiedSpace(HexNode* target) = 0;
		virtual std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player) = 0;
		virtual bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate) = 0;
};

#endif