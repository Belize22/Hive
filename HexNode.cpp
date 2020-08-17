#include "HexNode.h";

HexNode::HexNode() {
	_coordinate = new Coordinate();
	initializeNode();
}

HexNode::HexNode(Coordinate* coordinate, HexDirection direction) {
	//offsetCoordinate(coordinate, direction);
	_coordinate = new Coordinate(new int(coordinate->getX()), new int(coordinate->getY()), new int(coordinate->getZ()));
	initializeNode();
}

void HexNode::initializeNode() {
	/*_adjacentNodes = new std::vector<HexNode*>();
	for (int i = 0; i < 6; i++) {
		_adjacentNodes->push_back(nullptr);
	}*/
	_gamePiece = nullptr;
}


//std::vector<HexNode*>* HexNode::getAdjacentNodes() {
	//return _adjacentNodes;
//}

Coordinate* HexNode::getCoordinate() {
	return _coordinate;
}

GamePiece* HexNode::getGamePiece() {
	return _gamePiece;
}

void HexNode::setCoordinate(Coordinate* coordinate) {
	//delete _coordinate;
	_coordinate = coordinate;
}

void HexNode::setGamePiece(GamePiece* gamePiece) {
	//delete _gamePiece;
	_gamePiece = gamePiece;
	//setAdjacentNodes();
};

