#include "InputParser.h"

bool InputParser::isValidRegex(std::string input)
{
	if (std::regex_match(input.begin(), input.end(), placementRegex)) {
		std::cout << "Placing Piece" << std::endl;
		return true;
	}

	if (std::regex_match(input.begin(), input.end(), movementRegex)) {
		std::cout << "Moving Piece" << std::endl;
		return true;
	}

	if (input == PASS_STRING || input == TIE_STRING) {
		return true;
	}

	std::cout << "Invalid Input" << std::endl;
	return false;
}


GamePieceInteractionType InputParser::getGamePieceInteractionTypeFromInput(std::string& gamePieceInteractionTypeInput)
{
	std::smatch match;

	while (std::regex_search(gamePieceInteractionTypeInput, match, interactionTypeRegex)) {
		if (match.str() == "P") {
			gamePieceInteractionTypeInput = match.suffix().str();
			return PLACEMENT;
		}
		gamePieceInteractionTypeInput = match.suffix().str();
		return MOVEMENT;
	}
	return PLACEMENT; //Will never fire. Placed here for compiling purposes.
}

GamePieceType InputParser::getGamePieceTypeFromInput(std::string& gamePieceTypeInput) {
	std::smatch match;

	while (std::regex_search(gamePieceTypeInput, match, gamePieceTypeRegex))
	{
		if (match.str() == "Q") {
			gamePieceTypeInput = match.suffix().str();
			return QUEEN_BEE;
		}
		if (match.str() == "B") {
			gamePieceTypeInput = match.suffix().str();
			return BEETLE;
		}
		if (match.str() == "G") {
			gamePieceTypeInput = match.suffix().str();
			return GRASSHOPPER;
		}
		if (match.str() == "S") {
			gamePieceTypeInput = match.suffix().str();
			return SPIDER;
		}
		gamePieceTypeInput = match.suffix().str();
		return SOLDIER_ANT;
	}
	return QUEEN_BEE; //Will never fire. Placed here for compiling purposes.
}


GamePiece* InputParser::getGamePieceFromInput(Player* player, std::string& gamePieceInput) {
	std::smatch match;

	while (std::regex_search(gamePieceInput, match, gamePieceRegex)) {
		std::string gamePieceTypeInput = match.str().substr(0, 1);
		std::string gamePieceIndexInput = match.str().substr(1, 1);
		GamePieceType gamePieceType = getGamePieceTypeFromInput(gamePieceTypeInput);
		return player->getGamePieces()->at(static_cast<GamePieceType>(gamePieceType))->at(stoi(gamePieceIndexInput) - 1);
	}
	return nullptr; //Will never fire.
}

Coordinate* InputParser::getCoordinateFromInput(std::string coordinateInput) {
	std::smatch match;
	int x;
	int y;

	while (std::regex_search(coordinateInput, match, coordinateRegex)) {
		if (coordinateInput[0] == '(') {
			x = stoi(match.str());
		}
		else {
			y = stoi(match.str());
		}
		coordinateInput = match.suffix().str();
	}

	return new Coordinate(new int(x), new int (y), new int(0));
}
