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

	if (!destinationIsAdjacentToAnotherGamePiece(gamePiece->getHexNode(), coordinate))
	{
		std::cout << "Piece must be adjacent to at least one other piece!" << std::endl;
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

bool MovementStrategy::destinationIsAdjacentToAnotherGamePiece(HexNode* source, Coordinate* destCoord)
{
	HexNode* currentNode;
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++)
	{
		destCoord->offsetCoordinate(destCoord, static_cast<HexDirection>(mod(i, ADJACENT_HEX_DIRECTIONS)));
		currentNode = (_board->getGamePieces()->find(destCoord->toString()) !=
			_board->getGamePieces()->end()) ?
			_board->getGamePieces()->at(destCoord->toString()) : nullptr;
		destCoord->offsetCoordinate(destCoord, static_cast<HexDirection>(mod(i + 3, 6)));
		if (currentNode != source) //Disregard source since its game piece is the movement candidate.
		{
			if (currentNode != nullptr && currentNode->getGamePiece() != nullptr)
			{
				return true;
			}
		}
	}
	return false;
}

//Checks if the absence of a chosen game piece will separate the occupied hex nodes into multiple partitions
//(Illegal move for the player if that is the case).
bool MovementStrategy::respectsOHR(GamePiece* gamePiece)
{
	if (!surroundingGamePiecesAreDisjointed(gamePiece))
	{
		return true;
	}
	if (hiveWillSeparateAfterMovingPiece(gamePiece))
	{
		return false;
	}

	return true;
}

//Checks if the game piece is on the edge of the Hive.
//If so, then moving it won't separate the Hive.
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
	return gamePiecePartitions > 1;
}

//Closed loops formed in the Hive makes it so that moving a game piece that is in a center portion of the Hive
//may not separate the Hive. BFS is used to see if the candidate in question is part of anything else other
//than a closed loop or not (BFS will find every available spot in the Hive if that isn't the case).
bool MovementStrategy::hiveWillSeparateAfterMovingPiece(GamePiece* gamePiece)
{
	std::vector<HexNode*>* openList = new std::vector<HexNode*>();
	std::vector<HexNode*>* closedList = new std::vector<HexNode*>();
	Coordinate* currentCoordinate = gamePiece->getHexNode()->getCoordinate();
	HexNode* currentNode;
	bool foundOccupiedHexNode = false;

	//Find the first adjacent spot occupied by a game piece and use as starting point for BFS.
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) { //Must check the first adjacent spot twice for partition count purposes.
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i, ADJACENT_HEX_DIRECTIONS)));
		currentNode = (_board->getGamePieces()->at(currentCoordinate->toString())); //No coordinate should be null. Focused on adjacent spots of source piece.
		if (currentNode->getGamePiece() != nullptr && !foundOccupiedHexNode)
		{
			openList->push_back(currentNode);
			foundOccupiedHexNode = true;
		}
		else if (currentNode->getGamePiece() == nullptr) //Need to add available spots so that all hex nodes are explored if hive is not separated.
		{
			closedList->push_back(currentNode);
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
		else //Transfer current hex node from open list to closed list if no game piece occupies it (do not want to do BFS on available Hex nodes).
		{
			if (!std::count(closedList->begin(), closedList->end(), openList->at(0)))
			{
				closedList->push_back(openList->at(0));
			}
			openList->erase(openList->begin());
		}
	}

	return !(closedList->size() == _board->getGamePieces()->size());
}

//Generalized BFS algorithm for Hex node structure.
//Currently used for OHR verification.
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
		if (currentNode != nullptr && !std::count(closedList->begin(), closedList->end(), currentNode)) {
			openList->push_back(currentNode);
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
	if (!std::count(closedList->begin(), closedList->end(), currentHexNode)) {
		closedList->push_back(currentHexNode);
	}
}