#include "HexNode.h"

HexNode::HexNode() {
	_coordinate = new Coordinate();
	initializeNode();
}

HexNode::HexNode(Coordinate* coordinate) {
	_coordinate = new Coordinate(new int(coordinate->getX()), new int(coordinate->getY()), new int(coordinate->getZ()));
	initializeNode();
}

HexNode::~HexNode() {
	//Game piece not deleted (should always be nullptr when hex node is deleted)!
	delete _coordinate;
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

bool HexNode::operator==(const HexNode& other) {
	return *_coordinate == *other._coordinate; //Coordinate acts as unique identifier for Hex Node!
}



void HexNode::initializeNode() {
	_gamePiece = nullptr;
}
