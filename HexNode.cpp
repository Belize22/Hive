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
	_adjacentNodes = new std::vector<HexNode*>();
	for (int i = 0; i < 6; i++) {
		_adjacentNodes->push_back(nullptr);
	}
	_gamePiece = nullptr;
}


std::vector<HexNode*>* HexNode::getAdjacentNodes() {
	return _adjacentNodes;
}

Coordinate* HexNode::getCoordinate() {
	return _coordinate;
}

void HexNode::setCoordinate(Coordinate* coordinate) {
	delete _coordinate;
	_coordinate = coordinate;
}


void HexNode::setGamePiece(GamePiece* gamePiece) {
	delete _gamePiece;
	_gamePiece = gamePiece;
	setAdjacentNodes();
};

void HexNode::offsetCoordinate(Coordinate* coordinate, HexDirection direction) {
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

void HexNode::setAdjacentNodes() {
	HexNode* firstNode;
	if (_adjacentNodes->at(0) == nullptr) {
		firstNode = new HexNode(new Coordinate(*(this->getCoordinate())), static_cast<HexDirection>(0));
	}
	else {
		firstNode = _adjacentNodes->at(0);
	}
	HexNode* previousNode = nullptr;
	for (int i = 0; i < 6; i++) {	
		if (i == 0) {
			_adjacentNodes->at(i) = firstNode;
			previousNode = firstNode;
		}
		else {
			if (_adjacentNodes->at(i) == nullptr) {
				_adjacentNodes->at(i) = new HexNode(new Coordinate((*this->getCoordinate())), static_cast<HexDirection>(i));
			}
			((_adjacentNodes->at(i))->getAdjacentNodes())->at(mod(i - 2, 6)) = previousNode;
			(previousNode->getAdjacentNodes())->at(abs(i + 1) % 6) = _adjacentNodes->at(i);
			previousNode = _adjacentNodes->at(i);
			if (i == 5) {
				((_adjacentNodes->at(i))->getAdjacentNodes())->at(mod(i + 2, 6)) = firstNode;
				(firstNode->getAdjacentNodes())->at(mod(i - 1, 6)) = _adjacentNodes->at(i);
			}
		}
		((_adjacentNodes->at(i))->getAdjacentNodes())->at(mod(i - 3, 6)) = this;
	}
}

//% is remainder, not mod in C++
int HexNode::mod(int a, int b) {
	return (a % b + b) % b;
}