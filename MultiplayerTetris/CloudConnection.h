#pragma once
#ifndef CLOUDCONNECTION_H
#define CLOUDCONNECTION_H

#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Scrambler.h"

using json = nlohmann::json;
using namespace std;

class CloudConnection {
private:
	cpr::Session session;
	string serverURL;
	string* playerName;
	int* grid;
	int* opponentGrids;
	int gridSize;
	IntScrambler* score;
	bool* gameRunning;
	json multiplayerInfo;

	string GridToString();
	void StringToGrid(string gridString);
	void ParseMultiplayerInfo();

public:
	CloudConnection();
	CloudConnection(string* _playerName, int* _grid, int* _grids, int gridSize, IntScrambler* _score, bool* _gameRunning);
	bool JoinMultiplayerGame();
	bool SendSingleplayerRecord();
	bool SendMultiplayerInfo();
	void GetMultiplayerInfo();
	int GetHighScore();
	json GetHighScores();

};

#endif
#pragma once