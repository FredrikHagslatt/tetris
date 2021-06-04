#ifndef SERVER_CONNECTION_EMSCRIPTEN_H
#define SERVER_CONNECTION_EMSCRIPTEN_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#if defined(__EMSCRIPTEN__)
#include <emscripten/fetch.h>
#endif

class ServerConnectionEmscripten
{
public:

    int soloScore;
	std::vector<std::pair<std::string, int>> leaderboard;
	std::vector<std::pair<std::string, int>> ParseLeaderboard(std::string sLeaderboard);
	void FetchLeaderboard();
	void FetchSoloScore(std::string playerName);
	void PostHighscore(std::string playerName, int score);
	void RefreshLeaderboard();
	void RefreshSoloScore();
	ServerConnectionEmscripten();
};
#endif