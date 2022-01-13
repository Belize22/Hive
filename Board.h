#ifndef BOARD
#define BOARD

#include "HexNode.h"
#include "GamePieceStrategy.h"
#include "PlacementStrategy.h"

#include <iostream>
#include <vector>
#include <map>

#include "HexDirectionEnum.h"

class Board
{
private:
	std::map<std::string, HexNode*>* _gamePieces;
	HexNode* _root;
	GamePieceStrategy* _gamePieceStrategy;

public:
	Board();
	bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate); 
	void setAdjacentSpots(HexNode* target);
	std::vector<Coordinate*>* getPlacementCandidates(HexNode* start, Player* player);
	std::map<std::string, HexNode*>* getGamePieces();
	HexNode* getRoot();
};

#endif