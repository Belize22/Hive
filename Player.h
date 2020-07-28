#ifndef PLAYER
#define PLAYER

#include <vector>

#include "Board.h"
#include "GamePiece.h"

class Player
{
private:
	Board* _board;
	std::vector<GamePiece*>* _gamePieces;

public:
	Player(Board* board);
	std::vector<GamePiece*>* getGamePieces();
	bool placeGamePiece(Coordinate* coordinate);
};

#endif
