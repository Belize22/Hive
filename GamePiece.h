#ifndef GAME_PIECE
#define GAME_PIECE

#include "GamePieceTypeEnum.h"

class Board;
class Player;
class HexNode;

class GamePiece
{
private:
	Board* _board;
	Player* _player;
	HexNode* _hexNode;
	GamePieceType _gamePieceType;
	bool _active;
	bool _buried;

public:
	GamePiece(Board* board, Player* player, GamePieceType gamePieceType);
	Player* getPlayer();
	HexNode* getHexNode();
	void setHexNode(HexNode* hexNode);
};

#endif