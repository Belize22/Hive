#include "HexNode.h";

HexNode::HexNode() {
	for (int i = 0; i < 6; i++) {
		_adjacentNodes.push_back(nullptr);
	}
	_coordinate = new Coordinate();
}

Coordinate HexNode::getCoordinate() {
	return *_coordinate;
}

void HexNode::setCoordinate(Coordinate* coordinate) {
	_coordinate = coordinate;
}