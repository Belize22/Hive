#include "Player.h"

Player::Player(Board* board) {
	_board = board;
	_gamePieces = new std::vector<std::vector<GamePiece*>*>();
	for (int i = 0; i < AMOUNT_OF_PIECE_TYPES; i++)
	{
		_gamePieces->push_back(new std::vector<GamePiece*>());
		for (int j = 0; j < PIECE_AMOUNTS[i]; j++)
		{
			_gamePieces->at(i)->push_back(new GamePiece(board, this, static_cast<GamePieceType>(i)));
		}
	}
}

std::vector<std::vector<GamePiece*>*>* Player::getGamePieces() {
	return _gamePieces;
};

bool Player::placeGamePiece(Coordinate* coordinate, GamePieceType gamePieceType) {
	GamePiece* selectedGamePiece = nullptr;

	std::vector<GamePiece*>* currentGamePieceList = _gamePieces->at(static_cast<GamePieceType>(gamePieceType));

	for (int i = 0; i < currentGamePieceList->size(); i++)
	{
		if (currentGamePieceList->at(i)->getHexNode() == nullptr)
		{
			selectedGamePiece = currentGamePieceList->at(i);
			break;
		}
		else if (i == PIECE_AMOUNTS[static_cast<GamePieceType>(gamePieceType)] - 1)
		{
			std::cout << "The type of piece you want to place are all on the board!" << std::endl;
			return false;
		}
	}

	if (selectedGamePiece == nullptr) {
		return false;
	}

	bool isValidSpot = _board->handleGamePiece(selectedGamePiece, coordinate);
	return isValidSpot;
}