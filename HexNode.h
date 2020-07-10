#ifndef HEX_NODE
#define HEX_NODE

#include <vector>

#include "Coordinate.h"

class HexNode
{
private:
	std::vector<HexNode*> _adjacentNodes;
	Coordinate* _coordinate;

public:
	HexNode();
	Coordinate getCoordinate();
	void setCoordinate(Coordinate* coordinate);
};

#endif
