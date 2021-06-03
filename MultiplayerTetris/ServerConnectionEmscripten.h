#ifndef SERVER_CONNECTION_EMSCRIPTEN_H
#define SERVER_CONNECTION_EMSCRIPTEN_H

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

    int soloScore;
    vector<pair<string, int>> leaderboard;
	vector<pair<string, int>> ParseLeaderboard(string sLeaderboard);
	void FetchLeaderboard();
	void FetchSoloScore(string playerName);
	void PostHighscore(string playerName, int score);
	void RefreshLeaderboard();
	void RefreshSoloScore();
	ServerConnectionEmscripten();
};
#endif