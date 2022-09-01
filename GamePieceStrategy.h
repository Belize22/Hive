#ifndef GAME_PIECE_STRATEGY
#define GAME_PIECE_STRATEGY

class Board;
#include "GamePiece.h"
#include "Coordinate.h"
#include "HexNode.h"

#include <map>
#include <iostream>

const int ADJACENT_HEX_DIRECTIONS = 6;

class GamePieceStrategy
{
	private:
		bool onlyOnePiecePlaced();

	protected:
		Board* _board;
		bool pieceCanBePlaced(HexNode* target);
		bool spotExists(HexNode* target);
		bool spotIsAvailable(HexNode* target);
		bool spotAdjacentToOpposingPiece(Player* player, Coordinate* coordinate);

	public:
		GamePieceStrategy();
		GamePieceStrategy(Board* board);
		std::vector<Coordinate*>* getCandidates(HexNode* start, Player* player);
		void setAdjacentSpots(HexNode* target);
		bool queenBeeSurrounded(HexNode* queenBeeSpot);
		HexNode* getAdjacentHexNode(Coordinate* coordinate, int iteratorValue);
		virtual bool handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate) = 0;
		static int mod(int a, int b);
};
#endif