#ifndef HEX_NODE
#define HEX_NODE

#include <vector>
#include <cmath>

#include "Coordinate.h"
#include "GamePiece.h"

class HexNode {
	private:
		Coordinate* _coordinate;
		GamePiece* _gamePiece;

		void initializeNode();

	public:
		HexNode();
		HexNode(Coordinate* coordinate);
		~HexNode();
		Coordinate* getCoordinate();
		GamePiece* getGamePiece();
		void setCoordinate(Coordinate* coordinate);
		void setGamePiece(GamePiece* gamePiece);
		bool operator == (const HexNode& other);
};

#endif
