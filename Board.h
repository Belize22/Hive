#ifndef BOARD
#define BOARD

#include "HexNode.h"

#include <iostream>
#include <vector>

#include "HexDirectionEnum.h"

class Board
{
private:
	HexNode* _root;

public:
	Board();
	bool placeGamePiece(GamePiece* gamePiece, Coordinate* coordinate);
	std::vector<Coordinate*>* getPlacementCandidates(HexNode* start, Player* player);
	HexNode* getChosenPlacementCandidate(HexNode* start, Coordinate* coordinate);
	void advanceBFS(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList);
	HexNode* getRoot();
	bool spotAdjacentToOpposingPiece(Player* player, HexNode* spot);
	static bool isAPlacementCandidate(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList, HexNode* currentHexNode);
	static bool pieceCanBePlaced(HexNode* target);
};

#endif