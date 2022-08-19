#ifndef MULTI_SPACE_MOVEMENT_STRATEGY
#define MULTI_SPACE_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class MultiSpaceMovementStrategy : public MovementStrategy
{
protected:
	int maxDistance;
public:
	MultiSpaceMovementStrategy();
	MultiSpaceMovementStrategy(Board* board);
	bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate);
	bool traversingOnEdge(HexNode* node, HexDirection direction, HexNode* source);
	bool destinationReachableByDFS(HexNode* source, HexNode* destination);
	bool pieceCanMoveOnOccupiedSpace(HexNode* target);
	void advanceBFSMultiMove(std::vector<HexNode*>* openList, std::vector<int*>* openListDistances, std::vector<HexNode*>* closedList, HexNode* source);
	bool spotIsOccupied(HexNode* node, HexNode* source);
	virtual bool distanceConditionSatisfied(int* distance) = 0;
};

#endif