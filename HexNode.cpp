#include "HexNode.h";

HexNode::HexNode() {
	_coordinate = new Coordinate();
	initializeNode();
}

HexNode::HexNode(Coordinate* coordinate, HexDirection direction) {
	offsetCoordinate(coordinate, direction);
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
	delete _coordinate;
	_coordinate = coordinate;
}


void HexNode::setGamePiece(GamePiece* gamePiece) {
	delete _gamePiece;
	_gamePiece = gamePiece;
};

void HexNode::offsetCoordinate(Coordinate* coordinate, HexDirection direction) {
	//May need to plug potential memory leak here.
	coordinate->setCoordinate(new int(coordinate->getX() + horizontalDirectionOffset(direction)),
		new int(coordinate->getY() + verticalDirectionOffset(direction, coordinate->getX())), 
		new int(coordinate->getZ()));
}

int HexNode::horizontalDirectionOffset(HexDirection direction) {
	switch (direction) {
		case UP_RIGHT:
			return 1;
		case DOWN_RIGHT:
			return 1;
		case DOWN_LEFT:
			return -1;
		case UP_LEFT:
			return -1;
		default:
			return 0;
	}
}

int HexNode::verticalDirectionOffset(HexDirection direction, int xValue) {
	switch (direction) {
		case UP:
			return -1;
		case UP_RIGHT:
			return (xValue % 2 == 0 ? -1 : 0);
		case DOWN_RIGHT:
			return xValue % 2 == 0 ? 0 : 1;
		case DOWN:
			return 1;
		case DOWN_LEFT:
			return (xValue % 2 == 0 ? 0 : 1);
		case UP_LEFT:
			return xValue % 2 == 0 ? -1 : 0;
		default:
			return 0;
	}
}