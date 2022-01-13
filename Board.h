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
	bool placeGamePiece(GamePiece* gamePiece, Coordinate* coordinate); 
	void setAdjacentSpots(HexNode* target);
	std::vector<Coordinate*>* getPlacementCandidates(HexNode* start, Player* player);
	HexNode* getChosenPlacementCandidate(HexNode* start, Coordinate* coordinate);
	void advanceBFS(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList);
	std::map<std::string, HexNode*>* getGamePieces();
	HexNode* getRoot();
	bool spotAdjacentToOpposingPiece(Player* player, Coordinate* coordinate);
	bool onlyOnePiecePlaced();
	static bool isAPlacementCandidate(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList, HexNode* currentHexNode);
	static bool pieceCanBePlaced(HexNode* target); 
	static int mod(int a, int b);
};

#endif