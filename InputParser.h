#ifndef INPUT_PARSER
#define INPUT_PARSER

#include "Coordinate.h"
#include "GamePiece.h"
#include "GamePieceTypeEnum.h"
#include <iostream>
#include <string>
#include <regex>

const std::regex placementRegex("P[ABGQS]\\([-]?[0-9]+,[-]?[0-9]+\\)");     //ex: PQ(-1,1)
const std::regex movementRegex("M[ABGQS][0-9]\\([-]?[0-9]+,[-]?[0-9]+\\)"); //ex: MS1(0,-2)

class InputParser 
{
public:
	static bool isValidRegex(std::string input);
	static Coordinate* getCoordinateFromInput(std::string coordinateInput);
	static GamePieceType getGamePieceTypeFromInput(std::string gamePieceTypeInput); //Placement only.
	static GamePiece getGamePieceFromInput(std::string); //Movement only.
};

#pragma once

#endif
