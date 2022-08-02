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
};

#endif