#ifndef BOARD
#define BOARD

#include "HexNode.h"
#include <vector>

#include "HexDirectionEnum.h"

class Board
{
private:
	HexNode* _root;

public:
	Board();
	void placeGamePiece(GamePiece* gamePiece, Coordinate* coordinate);
	std::vector<Coordinate*>* getPlacementCandidates(HexNode* start);
	HexNode* getChosenPlacementCandidate(HexNode* start, Coordinate* coordinate);
	void advanceBFS(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList);
	HexNode* getRoot();
	static bool isAPlacementCandidate(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList, HexNode* currentHexNode);
};

#endif