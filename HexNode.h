#ifndef HEX_NODE
#define HEX_NODE

#include <vector>

#include "Coordinate.h"
#include "GamePiece.h"

#include "HexDirectionEnum.h"

class HexNode
{

private:
	std::vector<HexNode*> _adjacentNodes;
	Coordinate* _coordinate;
	GamePiece* _gamePiece;
	int horizontalDirectionOffset(HexDirection direction);
	int verticalDirectionOffset(HexDirection direction, int xValue);

public:
	HexNode();
	HexNode(Coordinate* coordinate, HexDirection direction);
	void initializeNode();
	Coordinate getCoordinate();
	void setCoordinate(Coordinate* coordinate);
	void offsetCoordinate(Coordinate* coordinate, HexDirection direction);
};

#endif
