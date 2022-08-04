#ifndef GRASSHOPPER_MOVEMENT_STRATEGY
#define GRASSHOPPER_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class GrasshopperMovementStrategy : public MovementStrategy
{
public:
	GrasshopperMovementStrategy();
	GrasshopperMovementStrategy(Board* board);
	bool pieceCanMoveOnOccupiedSpace(HexNode* target);
	bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate);
	bool sourceAndDestinationAreAligned(HexNode* source, HexNode* destination);
	bool nodesBetweenSourceAndDestinationAreOccupied(HexNode* source, HexNode* destination, HexDirection direction);
	HexDirection getDirectionToDestination(HexNode* source, HexNode* destination);
	bool verifyDiagonalAlignment(HexNode* source, HexNode* destination, int yOffset);
};

#endif