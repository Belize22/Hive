#ifndef GAME_PIECE_STRATEGY
#define GAME_PIECE_STRATEGY

#pragma once

class Board;
#include "GamePiece.h"
#include "Coordinate.h"
#include "HexNode.h"

#include <map>
#include <iostream>

class GamePieceStrategy
{
protected:
	Board* _board;
public:
	GamePieceStrategy();
	GamePieceStrategy(Board* board);
	std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player);
	void setAdjacentSpots(HexNode* target);
	bool pieceCanBePlaced(HexNode* target);
	bool spotAdjacentToOpposingPiece(Player* player, Coordinate* coordinate);
	void advanceBFS(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList);
	bool onlyOnePiecePlaced();
	bool isAPlacementCandidate(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList, HexNode* currentHexNode);
	virtual bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate) = 0;
	static int mod(int a, int b);
};
#endif