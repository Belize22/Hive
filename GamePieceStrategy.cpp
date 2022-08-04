#include "GamePieceStrategy.h"
#include "Board.h"

GamePieceStrategy::GamePieceStrategy()
{

}

GamePieceStrategy::GamePieceStrategy(Board* board) {
	_board = board;
}

void GamePieceStrategy::setAdjacentSpots(HexNode* target) {
	HexNode* currentNode;
	Coordinate* currentCoordinate = target->getCoordinate();
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(i)); //Get coordinates of specified adjacent direction.
		HexNode* currentNode = (_board->getGamePieces()->find(currentCoordinate->toString()) !=
			_board->getGamePieces()->end()) ?
			_board->getGamePieces()->at(currentCoordinate->toString()) : nullptr;
		if (currentNode == nullptr) {
			_board->getGamePieces()->insert(std::pair<std::string, HexNode*>(currentCoordinate->toString(), new HexNode(new Coordinate(*currentCoordinate))));
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6))); //Return to original hex location to avoid going off-center!
	}
}

std::vector<Coordinate*>* GamePieceStrategy::getCandidates(HexNode* start, Player* player)
{
	std::map<std::string, HexNode*>::iterator it = _board->getGamePieces()->begin();
	std::vector<Coordinate*>* freeSpots = new std::vector<Coordinate*>();
	while (it != _board->getGamePieces()->end())
	{
		HexNode* currentHexNode = it->second;
		Coordinate* coordinate = currentHexNode->getCoordinate();

		if (currentHexNode->getGamePiece() == nullptr && (!spotAdjacentToOpposingPiece(player, coordinate) || onlyOnePiecePlaced()))
		{
			freeSpots->push_back(coordinate);
		}
		it++;
	}
	return freeSpots;
}

bool GamePieceStrategy::pieceCanBePlaced(HexNode* target) {
	return spotExists(target) && spotIsAvailable(target);
}

bool GamePieceStrategy::spotExists(HexNode* target)
{
	return target != nullptr;
}

bool GamePieceStrategy::spotIsAvailable(HexNode* target)
{
	return target->getGamePiece() == nullptr;
}

bool GamePieceStrategy::spotAdjacentToOpposingPiece(Player* player, Coordinate* coordinate) {
	if (onlyOnePiecePlaced()) {
		return false;
	}
	HexNode* currentNode;
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) 
	{
		currentNode = getAdjacentHexNode(coordinate, i);
		HexNode* candidateNode = currentNode;

		if (candidateNode != nullptr)
		{
			Coordinate* currentCoordinate = new Coordinate(new int(currentNode->getCoordinate()->getX()), new int(currentNode->getCoordinate()->getY()), new int(0));

			//Need to get topmost piece of adjacent coordinate (takes priority for checking if potential placement is next to piece of opposing player.
			while (candidateNode != nullptr)
			{
				currentNode = candidateNode;
				currentCoordinate->incrementZ();
				candidateNode = (_board->getGamePieces()->find(currentCoordinate->toString()) !=
					_board->getGamePieces()->end()) ?
					_board->getGamePieces()->at(currentCoordinate->toString()) : nullptr;
			}

			delete currentCoordinate;
		}

		if (currentNode != nullptr && currentNode->getGamePiece() != nullptr && currentNode->getGamePiece()->getPlayer() != player) 
		{
			return true;
		}
	}
	return false;
}

//To allow the second to be placed adjacent to it. Not allowed for all other scenarios).
//The scenario where a beetle and another piece below it are the only existing pieces will never happen since you cannot move
//Beetles above game pieces until the player's Queen Bee has been placed!
bool GamePieceStrategy::onlyOnePiecePlaced() {
	HexNode* currentNode = _board->getMostRecentSpot();
	Coordinate* currentCoordinate = new Coordinate(new int(currentNode->getCoordinate()->getX()), new int(currentNode->getCoordinate()->getY()), new int(0));
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentNode = getAdjacentHexNode(currentCoordinate, i);
		if (currentNode != nullptr && currentNode->getGamePiece() != nullptr) {
			return false;
		}
	}
	delete currentCoordinate;
	return true;
}

/*bool GamePieceStrategy::isAPlacementCandidate(std::vector<HexNode*>* openList, std::vector<HexNode*>* closedList, HexNode* currentHexNode) {
	for (size_t i = 0; i < openList->size(); i++) {
		if (currentHexNode == openList->at(i)) {
			return false;
		}
	}
	for (size_t i = 0; i < closedList->size(); i++) {
		if (currentHexNode == closedList->at(i)) {
			return false;
		}
	}
	return true;
}*/

HexNode* GamePieceStrategy::getAdjacentHexNode(Coordinate* coordinate, int iteratorValue)
{
	coordinate->offsetCoordinate(coordinate, static_cast<HexDirection>(iteratorValue)); //Get coordinates of specified adjacent direction.
	HexNode* currentNode = (_board->getGamePieces()->find(coordinate->toString()) !=
		_board->getGamePieces()->end()) ?
		_board->getGamePieces()->at(coordinate->toString()) : nullptr;
	coordinate->offsetCoordinate(coordinate, static_cast<HexDirection>(mod(iteratorValue + 3, 6))); //Return to original hex location to avoid going off-center!
	return currentNode;
}

//% is remainder, not mod in C++
int GamePieceStrategy::mod(int a, int b) {
	return (a % b + b) % b;
}