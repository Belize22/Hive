#ifndef GAME_PIECE_STRATEGY
#define GAME_PIECE_STRATEGY

#pragma once

#include "Board.h"
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
	GamePieceStrategy(Board* board);
	void setAdjacentSpots(HexNode* target);
	virtual void handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate, std::map<std::string, HexNode*>* gamePieces) const = 0;
	virtual void getCandidates(HexNode* start, Player* player) const = 0;
	static int mod(int a, int b);
};
#endif