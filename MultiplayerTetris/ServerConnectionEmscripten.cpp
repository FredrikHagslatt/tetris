#include "ServerConnectionEmscripten.h"

string sLeaderboard = "FREPPAN,59;KARIN,35;RAJ,34;GANDALF,28";
ServerConnectionEmscripten::ServerConnectionEmscripten() { FetchLeaderboard(); }

#if defined(__EMSCRIPTEN__)
void getSucceeded(emscripten_fetch_t *fetch) {
    sLeaderboard = "";
    for (int i = 0; i < fetch->numBytes-1; i++){
        sLeaderboard += fetch->data[i];
    }
    emscripten_fetch_close(fetch); // Free data associated with the fetch.
}

void getFailed(emscripten_fetch_t* fetch) {
    printf("Failed to get leaderboard");
    emscripten_fetch_close(fetch); // Also free data on failure.
}

void postSucceeded(emscripten_fetch_t* fetch) {
    emscripten_fetch_close(fetch); // Free data associated with the fetch.
}

void postFailed(emscripten_fetch_t* fetch) {
    printf("Failed to send score");
    emscripten_fetch_close(fetch); // Also free data on failure.
}

void ServerConnectionEmscripten::FetchLeaderboard() {
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = getSucceeded;
    attr.onerror = getFailed;
    emscripten_fetch(&attr, "get_leaderboard.php");
}

void ServerConnectionEmscripten::PostHighscore(string playerName, int score) {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = postSucceeded;
    attr.onerror = postFailed;

    const char* headers[] = { "Content-Type", "application/x-www-form-urlencoded", 0 };
    attr.requestHeaders = headers;

    attr.requestData = "playerName=" + playerName + "&score=" score;
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
    leaderboard = ParseLeaderboard(sLeaderboard);
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
