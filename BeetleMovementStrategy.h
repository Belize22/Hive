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
	bool isMovementProper(HexNode* source, HexNode& destination);
	void changeToLowestZValueOfAvailableDestinationCoordinate(HexNode& destination);
};

#endif
