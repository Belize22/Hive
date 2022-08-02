#ifndef BEETLE_MOVEMENT_STRATEGY
#define BEETLE_MOVEMENT_STRATEGY

class Board;
#include "OneSpaceMovementStrategy.h"

class BeetleMovementStrategy : public OneSpaceMovementStrategy
{
public:
	BeetleMovementStrategy();
	BeetleMovementStrategy(Board* board); 
	bool pieceCanMoveOnOccupiedSpace(HexNode* target);
	bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate);
	HexNode* getLowestGamePieceForSource(HexNode* source);
	void changeToLowestZValueOfAvailableDestinationCoordinate(HexNode* destination, Coordinate& destinationCoordinate);
};

#endif
