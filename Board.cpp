#include "Board.h"

Board::Board() {
	//TODO: Need to implement custom comparators for map (or find another suitable data structure).
    _gamePieces = std::map<int, int>();
	//_gamePieces = std::map<GamePiece, Coordinate>();
	//Coordinate * coordinate = new Coordinate(0, 0, 0);
	//GamePiece * gamePiece = new GamePiece(*coordinate);
	//_gamePieces.insert(std::pair<GamePiece, Coordinate>(*gamePiece, *coordinate));
}

//void Board::placeGamePiece(GamePiece * gamePiece) {
	//_gamePieces.insert(std::pair<GamePiece, Coordinate>(*gamePiece, *(gamePiece->getPosition())));
//}

//void Board::moveGamePiece(GamePiece * gamePiece) {
	//_gamePieces[gamePiece] = gamePiece->getPosition();
//}
