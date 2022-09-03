#ifndef SOLDIER_ANT_MOVEMENT_STRATEGY
#define SOLDIER_ANT_MOVEMENT_STRATEGY

class Board;
#include "MultiSpaceMovementStrategy.h"

class SoldierAntMovementStrategy : public MultiSpaceMovementStrategy {
	protected:
		bool distanceConditionSatisfied(int* distance);

	public:
		SoldierAntMovementStrategy();
		SoldierAntMovementStrategy(Board* board);
		std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player);
};

#endif
