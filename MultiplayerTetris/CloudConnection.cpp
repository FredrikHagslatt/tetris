#include "CloudConnection.h"

CloudConnection::CloudConnection()
    : serverURL("http://backend.freppan.com/tetris/")
    , playerName(nullptr)
    , grid(nullptr)
    , opponentGrids(nullptr)
    , gridSize(0)
    , gameRunning(nullptr)
    , score(nullptr) {}


CloudConnection::CloudConnection(string* _playerName, int* _grid, int* _opponentGrids, int _gridSize, IntScrambler* _score, bool* _gameRunning)
    : serverURL("http://backend.freppan.com/tetris/")
    , playerName(_playerName)
    , grid(_grid)
    , opponentGrids(_opponentGrids)
    , gridSize(_gridSize)
    , gameRunning(_gameRunning)
    , score(_score) {}


string CloudConnection::GridToString() {
    string sendString;
    for (int* iterator = grid; iterator < grid + gridSize; iterator++) {
        sendString = sendString + to_string(*iterator);
    }
    return sendString;
}


void CloudConnection::StringToGrid(string gridString) {
    int i = 0;
    for (int* iterator = grid; iterator < grid + gridSize; iterator++) {
        *iterator = gridString[i++] - 48; //numbers start at ascii 48
    }
}


bool CloudConnection::JoinMultiplayerGame() {
    session.SetUrl(serverURL + "join_multiplayer_game.php");
    session.SetPayload({ {"playerName", *playerName}, {"gameid", 13}, {"grid", "0123"}, {"gameOver", false} });
    cpr::Response response = session.Post();
    return (response.status_code == 200);
}


bool CloudConnection::SendSingleplayerRecord() {
    session.SetUrl(serverURL + "save_singleplayer_record.php");
    session.SetPayload({ {"playerName", *playerName}, {"score", to_string(score->GetArticle())} });
    cpr::Response response = session.Post();
    return (response.status_code == 200 && response.text == "OK");
}


bool CloudConnection::SendMultiplayerInfo() {
    session.SetUrl(serverURL + "send_multiplayer_info.php");
    session.SetPayload({ {"grid", GridToString()}, {"gameOver", *gameRunning} });
    cpr::Response response = session.Post();
    return (response.status_code == 200 && response.text == "OK");
}


void CloudConnection::ParseMultiplayerInfo() {
    StringToGrid(multiplayerInfo["0"]["grid"]);
}


void CloudConnection::GetMultiplayerInfo() {
    session.SetUrl(serverURL + "get_multiplayer_info.php");
    cpr::Response response = session.Get();
    if (response.status_code == 200) {
        multiplayerInfo = json::parse(response.text);
    }
}


int CloudConnection::GetHighScore() {
    session.SetUrl(serverURL + "get_highscore.php");
    session.SetPayload({ {"playerName", *playerName} });

    int highestScore = 0;
    cpr::Response response = session.Post();
    if (response.status_code == 200) {
        highestScore = stoi(response.text);
    }
    return highestScore;
}


json CloudConnection::GetHighScores() {
    session.SetUrl(serverURL + "get_highscores.php");
    cpr::Response response = session.Get();
    json response_json;
    if (response.status_code == 200) {
        response_json = json::parse(response.text);
    }
    return response_json;
}

