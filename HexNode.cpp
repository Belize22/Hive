#include "HexNode.h";

HexNode::HexNode() {
	_coordinate = new Coordinate();
	initializeNode();
}

HexNode::HexNode(Coordinate* coordinate, HexDirection direction) {
	offsetCoordinate(coordinate, direction);
	delete[] _coordinate;
	_coordinate = new Coordinate(new int(coordinate->getX()), new int(coordinate->getY()), new int(coordinate->getZ()));
	initializeNode();
}

void HexNode::initializeNode() {
	for (int i = 0; i < 6; i++) {
		_adjacentNodes.push_back(nullptr);
	}
	_gamePiece = nullptr;
}

Coordinate HexNode::getCoordinate() {
	return *_coordinate;
}

void HexNode::setCoordinate(Coordinate* coordinate) {
	_coordinate = coordinate;
}

void HexNode::offsetCoordinate(Coordinate* coordinate, HexDirection direction) {
	coordinate->setCoordinate(new int(coordinate->getX()), new int(coordinate->getY()), new int(2));
}