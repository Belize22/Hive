#ifndef GAME_PIECE
#define GAME_PIECE

class Board;
class Player;
class HexNode;

class GamePiece
{
private:
	Board* _board;
	Player* _player;
	HexNode* _hexNode;
	bool _active;
	bool _buried;

public:
	GamePiece(Board* board, Player* player);
	Player* getPlayer();
};

#endif