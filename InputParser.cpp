#include "InputParser.h"

bool InputParser::isValidRegex(std::string input)
{
	if (std::regex_match(input.begin(), input.end(), placementRegex))
	{
		std::cout << "Placing Piece" << std::endl;
		return true;
	}
	else if (std::regex_match(input.begin(), input.end(), movementRegex))
	{
		std::cout << "Moving Piece" << std::endl;
		return true;
	}
	std::cout << "Invalid Input" << std::endl;
	return false;
}