#pragma once
#include <string>
#include "nlohmann/json.hpp"

/*
#if defined(__EMSCRIPTEN__)
#else
#endif
*/

using json = nlohmann::json;


using namespace std;
class ServerConnectionEmscripten
{
	string mockLeaderboard = "{ \"0\":{\"playerName\":\"FREPPAN\",\"score\" : \"59\"},\"1\" : {\"playerName\":\"KARIN\",\"score\" : \"35\"},\"2\" : {\"playerName\":\"RAJ\",\"score\" : \"34\"},\"3\" : {\"playerName\":\"GANDALF\",\"score\" : \"28\"},\"4\" : {\"playerName\":\"FIPPOO\",\"score\" : \"28\"},\"5\" : {\"playerName\":\"MANJIT\",\"score\" : \"25\"},\"6\" : {\"playerName\":\"FIPPO\",\"score\" : \"22\"},\"7\" : {\"playerName\":\"FIII\",\"score\" : \"20\"},\"8\" : {\"playerName\":\"RAGGIS\",\"score\" : \"20\"},\"9\" : {\"playerName\":\"ROBBELIBOBBA\",\"score\" : \"19\"},\"10\" : {\"playerName\":\"QWE\",\"score\" : \"3\"},\"11\" : {\"playerName\":\"EKAS\",\"score\" : \"2\"},\"12\" : {\"playerName\":\"ASDASD\",\"score\" : \"1\"},\"13\" : {\"playerName\":\"ASD\",\"score\" : \"0\"} }";

public:
	json leaderboard = json::parse(mockLeaderboard);
	void FetchLeaderboard();
	ServerConnectionEmscripten();

};
