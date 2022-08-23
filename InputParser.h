#ifndef INPUT_PARSER
#define INPUT_PARSER

#include "Coordinate.h"
#include "Player.h"
#include "GamePiece.h"
#include "GamePieceTypeEnum.h"
#include "GamePieceInteractionType.h"
#include <iostream>
#include <string>
#include <regex>

const std::string PASS_STRING = "PASS";
const std::string TIE_STRING = "TIE";

const std::regex placementRegex("P[ABGQS]\\([-]?[0-9]+,[-]?[0-9]+\\)");     //ex: PQ(-1,1)
const std::regex movementRegex("M[ABGQS][0-9]\\([-]?[0-9]+,[-]?[0-9]+\\)"); //ex: MS1(0,-2)
const std::regex interactionTypeRegex("^[MP]");
const std::regex gamePieceTypeRegex("^[ABGQS]");
const std::regex gamePieceRegex("^[ABGQS][0-9]");
const std::regex coordinateRegex("[-]?[0-9]");

class InputParser 
{
public:
	static bool isValidRegex(std::string input);
	static GamePieceInteractionType getGamePieceInteractionTypeFromInput(std::string& gamePieceInteractionTypeInput);
	static GamePieceType getGamePieceTypeFromInput(std::string& gamePieceTypeInput); //Placement only.
	static GamePiece* getGamePieceFromInput(Player* player, std::string& gamePieceInput); //Movement only.
	static Coordinate* getCoordinateFromInput(std::string coordinateInput);
};

#pragma once

#endif
