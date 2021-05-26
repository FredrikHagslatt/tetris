#include "ServerConnectionEmscripten.h"

string globString = "FREPPAN,59;KARIN,35;RAJ,34;GANDALF,28";
ServerConnectionEmscripten::ServerConnectionEmscripten() { FetchLeaderboard(); }

#if defined(__EMSCRIPTEN__)
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

void ServerConnectionEmscripten::FetchLeaderboard() {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = downloadSucceeded;
    attr.onerror = downloadFailed;
//    emscripten_fetch(&attr, "info.json");
    emscripten_fetch(&attr, "get_leaderboard.php");
    cout << "FetchLeaderboard " << globString << endl;
}

void ServerConnectionEmscripten::PostHighscore(string playerName, int score) {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = downloadSucceeded;
    attr.onerror = downloadFailed;

    const char* headers[] = { "Content-Type", "application/x-www-form-urlencoded", 0 };
    attr.requestHeaders = headers;

    attr.requestData = "playerName=deWASM&score=3";
    attr.requestDataSize = strlen(attr.requestData);
    emscripten_fetch(&attr, "save_singleplayer_record.php");
}

#else
void ServerConnectionEmscripten::FetchLeaderboard() {}
void ServerConnectionEmscripten::PostHighscore(string playerName, int score) {
    cout << "Posting " << endl;
}

#endif


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
