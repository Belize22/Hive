#ifndef GRASSHOPPER_MOVEMENT_STRATEGY
#define GRASSHOPPER_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class GrasshopperMovementStrategy : public MovementStrategy {
	private:
		HexDirection getDirectionToDestination(HexNode* source, HexNode* destination);
		bool nodesBetweenSourceAndDestinationAreOccupied(HexNode* source, HexNode* destination, HexDirection direction);
		bool sourceAndDestinationAreAligned(HexNode* source, HexNode* destination);
		bool verifyDiagonalAlignment(HexNode* source, HexNode* destination, int yOffset);

	public:
		GrasshopperMovementStrategy();
		GrasshopperMovementStrategy(Board* board);
		bool pieceCanMoveOnOccupiedSpace(HexNode* target);
		std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player);
		bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate);
};

#endif