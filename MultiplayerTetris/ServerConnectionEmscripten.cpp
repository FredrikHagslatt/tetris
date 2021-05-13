#include "ServerConnectionEmscripten.h"

string globString = "FREPPAN,59;KARIN,35;RAJ,34;GANDALF,28";

#if defined(__EMSCRIPTEN__)

//string globString = "{ \"0\":{\"playerName\":\"FREPPAN\",\"score\" : \"59\"},\"1\" : {\"playerName\":\"KARIN\",\"score\" : \"35\"},\"2\" : {\"playerName\":\"RAJ\",\"score\" : \"34\"},\"3\" : {\"playerName\":\"GANDALF\",\"score\" : \"28\"},\"4\" : {\"playerName\":\"FIPPOO\",\"score\" : \"28\"},\"5\" : {\"playerName\":\"MANJIT\",\"score\" : \"25\"},\"6\" : {\"playerName\":\"FIPPO\",\"score\" : \"22\"},\"7\" : {\"playerName\":\"FIII\",\"score\" : \"20\"},\"8\" : {\"playerName\":\"RAGGIS\",\"score\" : \"20\"},\"9\" : {\"playerName\":\"ROBBELIBOBBA\",\"score\" : \"19\"},\"10\" : {\"playerName\":\"QWE\",\"score\" : \"3\"},\"11\" : {\"playerName\":\"EKAS\",\"score\" : \"2\"},\"12\" : {\"playerName\":\"ASDASD\",\"score\" : \"1\"},\"13\" : {\"playerName\":\"ASD\",\"score\" : \"0\"} }";

void downloadSucceeded(emscripten_fetch_t *fetch) {
    printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
    // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
    globString = "";

    for (int i = 0; i < fetch->numBytes-1; i++){
        globString += fetch->data[i];
    }
    emscripten_fetch_close(fetch); // Free data associated with the fetch.
}

void downloadFailed(emscripten_fetch_t *fetch) {
    printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
    emscripten_fetch_close(fetch); // Also free data on failure.
}

#endif


ServerConnectionEmscripten::ServerConnectionEmscripten() { FetchLeaderboard(); }

void ServerConnectionEmscripten::FetchLeaderboard() {
#if defined(__EMSCRIPTEN__)


    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = downloadSucceeded;
    attr.onerror = downloadFailed;
    emscripten_fetch(&attr, "info.json");
    cout << "FetchLeaderboard " << globString << endl;
#endif

}

void ServerConnectionEmscripten::RefreshLeaderboard() {
    leaderboard = ParseLeaderboard(globString);
}

vector<pair<string, int>> ServerConnectionEmscripten::ParseLeaderboard(string sLeaderboard) {
    stringstream ssLeaderboard(sLeaderboard);
    vector<string> leaderboardSections;
    vector<pair<string, int>> vLeaderboard;

    while (ssLeaderboard.good()) {
        string substr;
        getline(ssLeaderboard, substr, ';');
        leaderboardSections.push_back(substr);
    }

    for (int i = 0; i < size(leaderboardSections); i++) {
        stringstream section(leaderboardSections[i]);
        string name;
        string num;
        getline(section, name, ',');
        getline(section, num, ',');
        vLeaderboard.push_back({ name, stoi(num) });
    }

    return vLeaderboard;
}
