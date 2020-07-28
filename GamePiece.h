#ifndef GAME_PIECE
#define GAME_PIECE

class Board;
class Player;

class GamePiece
{
private:
	Board* _board;
	Player* _player;
	bool _active;
	bool _buried;

public:
	GamePiece(Board* board, Player* player);
	Player* getPlayer();
};

#endif