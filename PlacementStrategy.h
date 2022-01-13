#ifndef PLACEMENT_STRATEGY
#define PLACEMENT_STRATEGY

#pragma once

class Board;
#include "GamePieceStrategy.h"
#include "GamePiece.h"
#include "Coordinate.h"

class PlacementStrategy : public GamePieceStrategy
{
public:
	PlacementStrategy();
	PlacementStrategy(Board* board);
	bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate);
	std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player);
	bool spotAdjacentToOpposingPiece(Player* player, Coordinate* coordinate);
	void advanceBFS(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList);
	bool onlyOnePiecePlaced();
	bool isAPlacementCandidate(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList, HexNode* currentHexNode);
};
#endif