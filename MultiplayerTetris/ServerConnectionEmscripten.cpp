#include "ServerConnectionEmscripten.h"

string sLeaderboard = "FREPPAN,59;KARIN,35;RAJ,34;GANDALF,28";
int iSoloScore = 0;
ServerConnectionEmscripten::ServerConnectionEmscripten() { FetchLeaderboard(); }

#if defined(__EMSCRIPTEN__)
void FetchLeaderboardSucceeded(emscripten_fetch_t *fetch) {
    sLeaderboard = "";
    for (int i = 0; i < fetch->numBytes-1; i++){
        sLeaderboard += fetch->data[i];
    }
    emscripten_fetch_close(fetch); // Free data associated with the fetch.
}


void FetchLeaderboardFailed(emscripten_fetch_t* fetch) {
    printf("Failed to get leaderboard");
    emscripten_fetch_close(fetch); // Also free data on failure.
}


void FetchSoloScoreSucceeded(emscripten_fetch_t *fetch) {
    string sSoloScore = "";
    for (int i = 0; i < fetch->numBytes; i++){
        sSoloScore += fetch->data[i];
    }
    iSoloScore = stoi(sSoloScore);
    emscripten_fetch_close(fetch); // Free data associated with the fetch.
}


void FetchSoloScoreFailed(emscripten_fetch_t* fetch) {
    printf("Failed to get best solo score");
    emscripten_fetch_close(fetch); // Also free data on failure.
}


void PostScoreSucceeded(emscripten_fetch_t* fetch) {
    emscripten_fetch_close(fetch); // Free data associated with the fetch.
}


void PostScoreFailed(emscripten_fetch_t* fetch) {
    printf("Failed to send score");
    emscripten_fetch_close(fetch); // Also free data on failure.
}


void ServerConnectionEmscripten::FetchLeaderboard() {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = FetchLeaderboardSucceeded;
    attr.onerror = FetchLeaderboardFailed;
    emscripten_fetch(&attr, "backend/get_leaderboard.php");
}


void ServerConnectionEmscripten::FetchSoloScore(string playerName) {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = FetchSoloScoreSucceeded;
    attr.onerror = FetchSoloScoreFailed;

    const char* headers[] = { "Content-Type", "application/x-www-form-urlencoded", 0 };
    attr.requestHeaders = headers;

    char data[100];
    strcpy(data, "playerName=");
    strcat(data, playerName.c_str());

    attr.requestData = data;
    attr.requestDataSize = strlen(attr.requestData);
    emscripten_fetch(&attr, "backend/fetch_solo_score.php");
}


void ServerConnectionEmscripten::PostHighscore(string playerName, int score) {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "POST");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = PostScoreSucceeded;
    attr.onerror = PostScoreFailed;

    const char* headers[] = { "Content-Type", "application/x-www-form-urlencoded", 0 };
    attr.requestHeaders = headers;

    char data[100];
    strcpy(data, "playerName=");
    strcat(data, playerName.c_str());
    strcat(data, "&score=");
    strcat(data, to_string(score).c_str());

    attr.requestData = data;
    attr.requestDataSize = strlen(attr.requestData);
    emscripten_fetch(&attr, "backend/save_singleplayer_record.php");
}

#else
void ServerConnectionEmscripten::FetchLeaderboard() {}
void ServerConnectionEmscripten::FetchSoloScore(string playerName) {}
void ServerConnectionEmscripten::PostHighscore(string playerName, int score) {}
#endif


void ServerConnectionEmscripten::RefreshLeaderboard() {
    leaderboard = ParseLeaderboard(sLeaderboard);
}

void ServerConnectionEmscripten::RefreshSoloScore() {
    soloScore = iSoloScore;
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
