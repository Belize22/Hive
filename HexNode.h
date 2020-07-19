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
	std::vector<HexNode*>* _adjacentNodes;
	Coordinate* _coordinate;
	GamePiece* _gamePiece;
	int horizontalDirectionOffset(HexDirection direction);
	int verticalDirectionOffset(HexDirection direction, int xValue);
	void setAdjacentNodes();

public:
	HexNode();
	HexNode(Coordinate* coordinate, HexDirection direction);
	void initializeNode();
	std::vector<HexNode*>* getAdjacentNodes();
	Coordinate* getCoordinate();
	void setCoordinate(Coordinate* coordinate);
	void setGamePiece(GamePiece* gamePiece);
	void offsetCoordinate(Coordinate* coordinate, HexDirection direction); 
	static int mod(int a, int b);
};

#endif
