#ifndef ONE_SPACE_MOVEMENT_STRATEGY
#define ONE_SPACE_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class OneSpaceMovementStrategy : public MovementStrategy
{
public:
	OneSpaceMovementStrategy();
	OneSpaceMovementStrategy(Board* board);
	int directionOfAdjacentDestination(HexNode* source, HexNode* destination);
	bool FTMRespectedForSpecifiedDirection(HexNode* source, HexDirection direction);
	bool isAdjacentDirectionShorter(HexNode* node, HexDirection direction, int directionOffset);
	bool areSourceAndDestinationAdjacent(HexNode* source, HexNode* destination, int direction);
	virtual bool pieceCanMoveOnOccupiedSpace(HexNode* target) = 0;
	virtual bool isMovementProper(HexNode* source, HexNode& destination) = 0;
};

#endif