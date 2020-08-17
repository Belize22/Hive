#ifndef HEX_NODE
#define HEX_NODE

#include <vector>
#include <cmath>

#include "Coordinate.h"
#include "GamePiece.h"

#include "HexDirectionEnum.h"

class HexNode
{

private:
	Coordinate* _coordinate;
	GamePiece* _gamePiece;

public:
	HexNode();
	HexNode(Coordinate* coordinate, HexDirection direction);
	void initializeNode();
	Coordinate* getCoordinate();
	GamePiece* getGamePiece();
	void setCoordinate(Coordinate* coordinate);
	void setGamePiece(GamePiece* gamePiece);
	static int mod(int a, int b);
};

#endif
