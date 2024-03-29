#include "MovementStrategy.h"
#include "Board.h"
#include "Player.h"

MovementStrategy::MovementStrategy() {

}

MovementStrategy::MovementStrategy(Board* board) {
	_board = board;
}

bool MovementStrategy::handleGamePiece(GamePiece* gamePiece, Coordinate* coordinate) {
	HexNode* source = gamePiece->getHexNode();
	HexNode* target = (_board->getHexNodes()->find(coordinate->toString()) !=
		_board->getHexNodes()->end()) ?
		_board->getHexNodes()->at(coordinate->toString()) : nullptr;

	if (!queenBeePlaced(gamePiece->getPlayer())) {
		std::cout << "Cannot move a piece until you place your Queen Bee!" << std::endl;
		return false;
	}

	if (isBuried(source)) {
		std::cout << "Piece is buried by another piece!" << std::endl;
		return false;
	}

	if (!spotExists(target))  {
		std::cout << "Destination spot is not adjacent to the Hive!" << std::endl;
		return false;
	}

	if (!spotIsAvailable(target)) {
		if (!pieceCanMoveOnOccupiedSpace(target)) { //To account for Beetles being able to move onto an occupied space!
			return false;
		}
	}

	if (!respectsOHR(gamePiece)) {
		std::cout << "Moving this piece will separate the Hive!" << std::endl;
		return false;
	}

	if (!isMovementProper(source, *coordinate)) {
		//Feedback to the user lies in subclass dedicated to the type of game piece.
		return false;
	}

	//z > 0 implies that destination is above another piece and therefore adjacent to the Hive
	if (!destinationIsAdjacentToAnotherGamePiece(source, coordinate) && coordinate->getZ() == 0) {
		std::cout << "Piece must be adjacent to at least one other piece!" << std::endl;
		return false;
	}
	
	//Remove spaces that are not adjacent to any game piece after movement is completed!
	if (source->getCoordinate()->getZ() == 0) { //z > 0 implies existence of game pieces below source!
		unsetAdjacentSpots(source);
	}
	gamePiece->setHexNode(nullptr);
	source->setGamePiece(nullptr);
	if (source->getCoordinate()->getZ() > 0) { //Available spots are only indicated if z = 0!
		_board->getHexNodes()->erase(_board->getHexNodes()->find(source->getCoordinate()->toString()));
	}

	//Retrieve again incase target coordinates changed (i.e. beetle moving to a coordinate where z > 0)
	target = (_board->getHexNodes()->find(coordinate->toString()) != _board->getHexNodes()->end()) ?
		_board->getHexNodes()->at(coordinate->toString()) : nullptr;

	//Add spaces that are adjacent to the moved game piece after movement is completed!
	gamePiece->setHexNode(target);
	target->setGamePiece(gamePiece);
	if (coordinate->getZ() == 0) {
		setAdjacentSpots(target);
	}
	_board->setMostRecentSpot(target);

	return true;
}



//In this context, can move piece means it can move to at least one specified destination.
bool MovementStrategy::canMovePiece(HexNode* source, Player* player) {
	if (!respectsOHR(source->getGamePiece())) {
		return false;
	}

	if (isBuried(source)) {
		return false;
	}

	if (!queenBeePlaced(player)) {
		return false;
	}

	return true;
}



void MovementStrategy::unsetAdjacentSpots(HexNode* target) {
	HexNode* currentNode;
	Coordinate* currentCoordinate = target->getCoordinate();
	HexNode* adjacentNode;
	Coordinate* adjacentCoordinate;
	bool freeSpotNeedsToExist;
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentNode = getAdjacentHexNode(currentCoordinate, i);
		adjacentCoordinate = currentNode->getCoordinate(); //Current node should never be null (since an occupied hex node is analyzed here).

		if (currentNode->getGamePiece() != nullptr) {
			continue; //Has a game piece. No adjacent spots require removal!
		}

		freeSpotNeedsToExist = false;
		for (int j = 0; j < ADJACENT_HEX_DIRECTIONS; j++) {
			adjacentNode = getAdjacentHexNode(adjacentCoordinate, j);
			if (adjacentNode != nullptr) {
				if (adjacentNode->getGamePiece() != nullptr && adjacentNode != target) { //Target will be in different location when moving anyways.
					freeSpotNeedsToExist = true;
				}
			}
		}

		if (!freeSpotNeedsToExist) {
			HexNode* clearedHexNode = _board->getHexNodes()->find(currentNode->getCoordinate()->toString())->second;
			_board->getHexNodes()->erase(_board->getHexNodes()->find(currentNode->getCoordinate()->toString()));
			delete clearedHexNode;
		}
	}
}

bool MovementStrategy::queenBeePlaced(Player* player) {
	return player->getGamePieces()->at(QUEEN_BEE)->at(0)->getHexNode() != nullptr;
}

bool MovementStrategy::isBuried(HexNode* source) {
	Coordinate* candidateCoordinate = new Coordinate(
		new int(source->getCoordinate()->getX()), 
		new int(source->getCoordinate()->getY()), 
		new int(source->getCoordinate()->getZ())
	);

	candidateCoordinate->incrementZ();
	HexNode* candidateNode = (_board->getHexNodes()->find(candidateCoordinate->toString()) != _board->getHexNodes()->end()) ?
		_board->getHexNodes()->at(candidateCoordinate->toString()) : nullptr;

	delete candidateCoordinate;

	if (spotExists(candidateNode)) {
		return true;
	}

	return false;
}

bool MovementStrategy::destinationIsAdjacentToAnotherGamePiece(HexNode* source, Coordinate* destCoord) {
	HexNode* currentNode;
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentNode = getAdjacentHexNode(destCoord, i);
		if (currentNode != source) { //Disregard source since its game piece is the movement candidate.
			if (currentNode != nullptr && currentNode->getGamePiece() != nullptr) {
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
	//z > 0 implies game piece(s) underneath. Therefore, no risk of violating OHR.
	if (gamePiece->getHexNode()->getCoordinate()->getZ() > 0) {
		return true;
	}

	if (!surroundingGamePiecesAreDisjointed(gamePiece)) {
		return true;
	}

	if (hiveWillSeparateAfterMovingPiece(gamePiece)) {
		return false;
	}

	return true;
}

//Checks if the game piece is on the edge of the Hive.
//If so, then moving it won't separate the Hive.
bool MovementStrategy::surroundingGamePiecesAreDisjointed(GamePiece* gamePiece) {
	HexNode* currentNode;
	Coordinate* currentCoordinate = gamePiece->getHexNode()->getCoordinate();
	int gamePiecePartitions = 0;
	bool lastAdjacentSpotHadGamePiece = false;

	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS + 1; i++) { //Must check the first adjacent spot twice for partition count purposes.
		currentNode = getAdjacentHexNode(currentCoordinate, mod(i, 6));

		if (!(currentNode->getGamePiece() != nullptr) && lastAdjacentSpotHadGamePiece) {
			gamePiecePartitions++;
		}

		lastAdjacentSpotHadGamePiece = currentNode->getGamePiece() != nullptr ? true : false;
	}
	return gamePiecePartitions > 1;
}

//Closed loops formed in the Hive makes it so that moving a game piece that is in a center portion of the Hive
//may not separate the Hive. BFS is used to see if the candidate in question is part of anything else other
//than a closed loop or not (BFS will find every available spot in the Hive if that isn't the case).
bool MovementStrategy::hiveWillSeparateAfterMovingPiece(GamePiece* gamePiece) {
	std::vector<HexNode*>* openList = new std::vector<HexNode*>();
	std::vector<HexNode*>* closedList = new std::vector<HexNode*>();
	Coordinate* currentCoordinate = gamePiece->getHexNode()->getCoordinate();
	HexNode* currentNode;
	bool foundOccupiedHexNode = false;

	//Find the first adjacent spot occupied by a game piece and use as starting point for BFS.
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) { //Must check the first adjacent spot twice for partition count purposes.
		currentNode = getAdjacentHexNode(currentCoordinate, i);
		if (currentNode->getGamePiece() != nullptr && !foundOccupiedHexNode) {
			openList->push_back(currentNode);
			foundOccupiedHexNode = true;
		}
		else if (currentNode->getGamePiece() == nullptr) {//Need to add available spots so that all hex nodes are explored if hive is not separated.
			closedList->push_back(currentNode);
		}
	}

	currentNode = (_board->getHexNodes()->at(currentCoordinate->toString())); //No coordinate should be null. Focused on adjacent spots of source piece.
	closedList->push_back(currentNode); //Movement candidate should be considered non-existent when verifying OHR.

	while (openList->size() > 0) {
		HexNode* currentHexNode = openList->at(0);
		if (currentHexNode->getGamePiece() != nullptr) { //Only game pieces should add all its adjacent spots to the open list.
			advanceBFS(openList, closedList);
		}
		else { //Transfer current hex node from open list to closed list if no game piece occupies it (do not want to do BFS on available Hex nodes).
			if (!std::count(closedList->begin(), closedList->end(), openList->at(0))) {
				closedList->push_back(openList->at(0));
			}
			openList->erase(openList->begin());
		}
	}

	bool isHiveSeparate = !(closedList->size() == _board->getHexNodes()->size());

	openList->clear();
	closedList->clear();
	delete openList;
	delete closedList;

	return isHiveSeparate;
}

//Generalized BFS algorithm for Hex node structure.
//Currently used for OHR verification.
void MovementStrategy::advanceBFS(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList) {
	HexNode* currentHexNode = openList->at(0);
	HexNode* currentNode;
	Coordinate* currentCoordinate = currentHexNode->getCoordinate();
	openList->erase(openList->begin());

	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentNode = getAdjacentHexNode(currentCoordinate, i);
		if (currentNode != nullptr && !std::count(closedList->begin(), closedList->end(), currentNode)) {
			openList->push_back(currentNode);
		}
	}

	if (!std::count(closedList->begin(), closedList->end(), currentHexNode)) {
		closedList->push_back(currentHexNode);
	}
}