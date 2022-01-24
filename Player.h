#ifndef PLAYER
#define PLAYER

#include <vector>

#include "Board.h"
#include "GamePiece.h"

const int AMOUNT_OF_PIECE_TYPES = 5;
//In order: Queen Bee, Beetle, Grasshopper, Spider, Soldier Ant
const int PIECE_AMOUNTS[AMOUNT_OF_PIECE_TYPES] = {1, 2, 3, 2, 3};

class Player
{
private:
	Board* _board;
	std::vector<std::vector<GamePiece*>*>* _gamePieces;

public:
	Player(Board* board);
	std::vector<std::vector<GamePiece*>*>* getGamePieces();
	bool placeGamePiece(Coordinate* coordinate, GamePieceType gamePieceType);
	bool moveGamePiece(Coordinate* coordinate, GamePiece* gamePiece);
};

#endif
