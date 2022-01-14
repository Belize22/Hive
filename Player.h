#ifndef PLAYER
#define PLAYER

#include <vector>

#include "Board.h"
#include "GamePiece.h"

const int QUEEN_BEE_AMOUNT = 1;
const int BEETLE_AMOUNT = 2;
const int GRASSHOPPER_AMOUNT = 3;
const int SPIDER_AMOUNT = 2;
const int SOLDIER_ANT_AMOUNT = 3;

class Player
{
private:
	Board* _board;
	std::vector<GamePiece*>* _gamePieces;

	GamePiece* _queenBee;
	std::vector<GamePiece*>* _beetles;
	std::vector<GamePiece*>* _grasshoppers;
	std::vector<GamePiece*>* _spiders;
	std::vector<GamePiece*>* _soldierAnts;

public:
	Player(Board* board);
	std::vector<GamePiece*>* getGamePieces();
	bool placeGamePiece(Coordinate* coordinate, GamePieceType gamePieceType);
};

#endif
