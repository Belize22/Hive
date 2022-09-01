#ifndef GAME_PIECE
#define GAME_PIECE

#include "GamePieceTypeEnum.h"

class Board;
class Player;
class HexNode;

class GamePiece {
	private:
		Board* _board;
		Player* _player;
		HexNode* _hexNode;
		GamePieceType _gamePieceType;

	public:
		GamePiece(Board* board, Player* player, GamePieceType gamePieceType);
		Player* getPlayer();
		HexNode* getHexNode();
		GamePieceType getGamePieceType();
		void setHexNode(HexNode* hexNode);
};

#endif