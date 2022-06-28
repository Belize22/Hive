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
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(i));
		currentNode = (_board->getGamePieces()->find(currentCoordinate->toString()) != 
			_board->getGamePieces()->end()) ? 
			_board->getGamePieces()->at(currentCoordinate->toString()) : nullptr;
		if (currentNode == nullptr) {
			_board->getGamePieces()->insert(std::pair<std::string, HexNode*>(currentCoordinate->toString(), new HexNode(new Coordinate(*currentCoordinate))));
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6))); //Return to original hex location!
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
	return target != nullptr && target->getGamePiece() == nullptr;
}

bool GamePieceStrategy::spotAdjacentToOpposingPiece(Player* player, Coordinate* coordinate) {
	if (onlyOnePiecePlaced()) {
		return false;
	}
	HexNode* currentNode;
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		coordinate->offsetCoordinate(coordinate, static_cast<HexDirection>(i));
		currentNode = (_board->getGamePieces()->find(coordinate->toString()) !=
			_board->getGamePieces()->end()) ?
			_board->getGamePieces()->at(coordinate->toString()) : nullptr;
		if (currentNode != nullptr && currentNode->getGamePiece() != nullptr && currentNode->getGamePiece()->getPlayer() != player) {
			coordinate->offsetCoordinate(coordinate, static_cast<HexDirection>(mod(i + 3, 6)));
			return true;
		}
		coordinate->offsetCoordinate(coordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
	return false;
}

bool GamePieceStrategy::onlyOnePiecePlaced() {
	HexNode* currentNode = _board->getMostRecentSpot();
	Coordinate* currentCoordinate = new Coordinate(new int(currentNode->getCoordinate()->getX()), new int(currentNode->getCoordinate()->getY()), new int(currentNode->getCoordinate()->getZ()));
	for (int i = 0; i < ADJACENT_HEX_DIRECTIONS; i++) {
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(i));
		currentNode = (_board->getGamePieces()->find(currentCoordinate->toString()) !=
			_board->getGamePieces()->end()) ?
			_board->getGamePieces()->at(currentCoordinate->toString()) : nullptr;
		if (currentNode != nullptr && currentNode->getGamePiece() != nullptr) {
			return false;
		}
		currentCoordinate->offsetCoordinate(currentCoordinate, static_cast<HexDirection>(mod(i + 3, 6)));
	}
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