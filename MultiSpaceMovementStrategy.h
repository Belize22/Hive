#ifndef MULTI_SPACE_MOVEMENT_STRATEGY
#define MULTI_SPACE_MOVEMENT_STRATEGY

class Board;
#include "MovementStrategy.h"

class MultiSpaceMovementStrategy : public MovementStrategy {
	private:
		bool traversingOnEdge(HexNode* node, HexDirection direction, HexNode* source); 
		bool destinationReachableByBFS(HexNode* source, HexNode* destination);
		std::vector<Coordinate*>* performMultiMoveBFS(HexNode* source, HexNode* destination);
		void advanceBFSMultiMove(std::vector<HexNode*>* openList, std::vector<int*>* openListDistances, std::vector<HexNode*>* closedList, std::vector<int*>* closedListDistances, HexNode* source);
		bool spotIsOccupied(HexNode* node, HexNode* source);

	protected:
		int maxDistance;
		virtual bool distanceConditionSatisfied(int* distance) = 0;

	public:
		MultiSpaceMovementStrategy();
		MultiSpaceMovementStrategy(Board* board);
		std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player);
		bool isMovementProper(HexNode* source, Coordinate& destinationCoordinate);
		bool pieceCanMoveOnOccupiedSpace(HexNode* target);
};

#endif