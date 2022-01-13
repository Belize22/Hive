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
	void setAdjacentSpots(HexNode* target);
	virtual bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate/*, std::map<std::string, HexNode*>* gamePieces*/) = 0;
	virtual std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player) = 0;
	static int mod(int a, int b);
};
#endif