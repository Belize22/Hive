#include "MovementStrategy.h"
#include "Board.h"

MovementStrategy::MovementStrategy() {

}

MovementStrategy::MovementStrategy(Board* board) {
	_board = board;
}

bool MovementStrategy::handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate)
{
	HexNode* source = gamePiece->getHexNode();
	HexNode* target = (_board->getGamePieces()->find(coordinate->toString()) !=
		_board->getGamePieces()->end()) ?
		_board->getGamePieces()->at(coordinate->toString()) : nullptr;
	if (!pieceCanBePlaced(target)) {
		if (target == nullptr) {
			std::cout << "Destination spot is not adjacent to the Hive!" << std::endl;
		}
		//Note: Beetle pieces can break this rule!
		else if (target->getGamePiece() != nullptr) {
			std::cout << "Destination spot is occupied!" << std::endl;
		}

		return false;
	}
	if (!respectsOHR(gamePiece))
	{
		std::cout << "Moving this piece will separate the Hive!" << std::endl;
		return false;
	}

	//TO-DO: Check if move respects Freedom to Move Rule
	
	unsetAdjacentSpots(source);
	gamePiece->setHexNode(nullptr);
	source->setGamePiece(nullptr);

	gamePiece->setHexNode(target);
	target->setGamePiece(gamePiece);
	setAdjacentSpots(target);
	_board->setMostRecentSpot(target);

	return true;
}

void MovementStrategy::unsetAdjacentSpots(HexNode* target)
{
	HexNode* currentNode;
	Coordinate* currentCoordinate = target->getCoordinate();
	HexNode* adjacentNode;
	Coordinate* adjacentCoordinate;
	bool freeSpotNeedsToExist;
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(i));
		currentNode = (_board->getGamePieces()->at(currentCoordinate->toString())); //No coordinate should be null. Focused on adjacent spot of source piece.
		adjacentCoordinate = currentCoordinate;
		if (currentNode->getGamePiece() != nullptr)
		{
			currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
			continue; //Has a game piece. No adjacent spots require removal!
		}
		freeSpotNeedsToExist = false;
		for (int j = 0; j < ADJACENT_HEX_DIRECTIONS; j++) {
			adjacentCoordinate->offsetCoordinate(adjacentCoordinate, static_cast<HexDirection>(j));
			adjacentNode = (_board->getGamePieces()->find(adjacentCoordinate->toString()) !=
				_board->getGamePieces()->end()) ?
				_board->getGamePieces()->at(adjacentCoordinate->toString()) : nullptr;
			if (adjacentNode != nullptr) {
				if (adjacentNode->getGamePiece() != nullptr && adjacentNode != target) //Target will be in different location when moving anyways.
				{
					freeSpotNeedsToExist = true;
				}
			}
			adjacentCoordinate->offsetCoordinate(adjacentCoordinate, static_cast<HexDirection>(mod(j + 3, 6)));
		}
		if (!freeSpotNeedsToExist) {
			_board->getGamePieces()->erase(_board->getGamePieces()->find(currentCoordinate->toString()));
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
}

std::vector<Coordinate*>* MovementStrategy::getCandidates(HexNode* start, Player* player)
{
	return new std::vector<Coordinate*>(); //Placeholder
}


bool MovementStrategy::respectsOHR(GamePiece* gamePiece)
{
	if (!surroundingGamePiecesAreDisjointed(gamePiece))
	{
		std::cout << "Partitions are not disjointed!" << std::endl;
		return true;
	}

	if (hiveWillSeparateAfterMovingPiece(gamePiece))
	{
		std::cout << "This move will separate the Hive!" << std::endl;
		return false;
	}

	std::cout << "Partitions are disjointed but this move won't separate the Hive!" << std::endl;
	return false;
}


bool MovementStrategy::surroundingGamePiecesAreDisjointed(GamePiece* gamePiece)
{
	HexNode* currentNode;
	Coordinate* currentCoordinate = gamePiece->getHexNode()->getCoordinate();
	int gamePiecePartitions = 0;
	bool lastAdjacentSpotHadGamePiece = false;
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS + 1; i++) { //Must check the first adjacent spot twice for partition count purposes.
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i, ADJACENT_HEX_DIRECTIONS)));
		currentNode = (_board->getGamePieces()->at(currentCoordinate->toString())); //No coordinate should be null. Focused on adjacent spots of source piece.
		if (!(currentNode->getGamePiece() != nullptr) && lastAdjacentSpotHadGamePiece)
		{
			gamePiecePartitions++;
		}
		lastAdjacentSpotHadGamePiece = currentNode->getGamePiece() != nullptr ? true : false;
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
	std::cout << "Partitions: " << gamePiecePartitions << std::endl;
	return gamePiecePartitions > 1;
}


bool MovementStrategy::hiveWillSeparateAfterMovingPiece(GamePiece* gamePiece)
{
	std::vector<HexNode*>* openList = new std::vector<HexNode*>();
	std::vector<HexNode*>* closedList = new std::vector<HexNode*>();
	Coordinate* currentCoordinate = gamePiece->getHexNode()->getCoordinate();
	HexNode* currentNode;

	//Find the first adjacent spot occupied by a game piece and use as starting point for BFS.
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) { //Must check the first adjacent spot twice for partition count purposes.
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i, ADJACENT_HEX_DIRECTIONS)));
		currentNode = (_board->getGamePieces()->at(currentCoordinate->toString())); //No coordinate should be null. Focused on adjacent spots of source piece.
		if (currentNode->getGamePiece() != nullptr)
		{
			openList->push_back(currentNode);
			currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
			break;
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}

	currentNode = (_board->getGamePieces()->at(currentCoordinate->toString())); //No coordinate should be null. Focused on adjacent spots of source piece.
	closedList->push_back(currentNode); //Movement candidate should be considered non-existent when verifying OHR.

	while (openList->size() > 0)
	{
		HexNode* currentHexNode = openList->at(0);
		if (currentHexNode->getGamePiece() != nullptr) //Only game pieces should add all its adjacent spots to the open list.
		{
			advanceBFS(openList, closedList);
		}
		else //Transfer current hex node from open list to closed list if no game piece occupies it.
		{
			closedList->push_back(openList->at(0));
			openList->erase(openList->begin());
		}
	}

	return !(closedList->size() == _board->getGamePieces()->size());
}

void MovementStrategy::advanceBFS(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList) {
	HexNode* currentHexNode = openList->at(0);
	HexNode* currentNode;
	Coordinate* currentCoordinate = currentHexNode->getCoordinate();
	openList->erase(openList->begin());
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(i));
		currentNode = (_board->getGamePieces()->find(currentCoordinate->toString()) !=
			_board->getGamePieces()->end()) ?
			_board->getGamePieces()->at(currentCoordinate->toString()) : nullptr;
		//TODO: Need to set custom equality method (or find an alternate method of comparison) for Hex Node class for closed list check to work!
		if (currentNode != nullptr && !std::count(closedList->begin(), closedList->end(), currentNode)) {
			openList->push_back(currentNode);
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
	closedList->push_back(currentHexNode);
}