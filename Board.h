#ifndef BOARD
#define BOARD

#include "HexNode.h"
#include "GamePieceStrategy.h"
#include "PlacementStrategy.h"
#include "MovementStrategy.h"
#include "Player.h"
#include "QueenBeeMovementStrategy.h"
#include "BeetleMovementStrategy.h"
#include "GrasshopperMovementStrategy.h"
#include "SpiderMovementStrategy.h"
#include "SoldierAntMovementStrategy.h"

#include <iostream>
#include <vector>
#include <map>

#include "HexDirectionEnum.h"

class Board {
	private:
		std::map<std::string, HexNode*>* _hexNodes;
		HexNode* _mostRecentSpot;
		PlacementStrategy* _placementStrategy;
		QueenBeeMovementStrategy* _queenBeeMovementStrategy;
		BeetleMovementStrategy* _beetleMovementStrategy;
		GrasshopperMovementStrategy* _grasshopperMovementStrategy;
		SpiderMovementStrategy* _spiderMovementStrategy;
		SoldierAntMovementStrategy* _soldierAntMovementStrategy;
		GamePieceStrategy* _gamePieceStrategy;
		MovementStrategy* getSpecifiedMovementStrategy(GamePieceType gamePieceType);

	public:
		Board();
		~Board();
		bool placeGamePiece(GamePiece* gamePiece, Coordinate* coordinate);
		bool moveGamePiece(GamePiece* gamePiece, Coordinate* coordinate);
		bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate); 
		void setAdjacentSpots(HexNode* target);
		std::vector<Coordinate*>* getPlacementCandidates(HexNode* start, Player* player); 
		std::vector<Coordinate*>* getMovementCandidates(HexNode* start, Player* player);
		std::map<std::string, HexNode*>* getHexNodes();
		bool isGameOver(Player* playerOne, Player* playerTwo);
		HexNode* getMostRecentSpot();
		void setMostRecentSpot(HexNode* mostRecentSpot);
};

#endif