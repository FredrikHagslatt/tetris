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
	string sLeaderboard = "FREPPAN,59;KARIN,35;RAJ,34;GANDALF,28";

public:

	vector<pair<string, int>> leaderboard;

	vector<pair<string, int>> ParseLeaderboard(string sLeaderboard);
	void FetchLeaderboard();
	void RefreshLeaderboard();
	ServerConnectionEmscripten();
};
