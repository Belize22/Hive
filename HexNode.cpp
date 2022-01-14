#include "HexNode.h"

HexNode::HexNode() {
	_coordinate = new Coordinate();
	initializeNode();
}

HexNode::HexNode(Coordinate* coordinate, HexDirection direction) {
	_coordinate = new Coordinate(new int(coordinate->getX()), new int(coordinate->getY()), new int(coordinate->getZ()));
	initializeNode();
}

void HexNode::initializeNode() {
	_gamePiece = nullptr;
}

Coordinate* HexNode::getCoordinate() {
	return _coordinate;
}

GamePiece* HexNode::getGamePiece() {
	return _gamePiece;
}

void HexNode::setCoordinate(Coordinate* coordinate) {
	_coordinate = coordinate;
}

void HexNode::setGamePiece(GamePiece* gamePiece) {
	_gamePiece = gamePiece;
};

