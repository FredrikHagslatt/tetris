#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#if defined(__EMSCRIPTEN__)
#include <emscripten/fetch.h>
#endif

using namespace std;

class ServerConnectionEmscripten
{
public:

	vector<pair<string, int>> leaderboard;
	vector<pair<string, int>> ParseLeaderboard(string sLeaderboard);
	void FetchLeaderboard();
	void PostHighscore(string playerName, int score);
	void RefreshLeaderboard();
	ServerConnectionEmscripten();
};