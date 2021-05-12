#include "LeaderboardScene.h"

void LeaderboardScene::Update(float fElapesedTime) {
    if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed) {
        sceneManager->ChangeScene(MENU);
    }
}

void LeaderboardScene::RenderGraphics() {
    serverCon.RefreshLeaderboard();

    engine->Clear(olc::DARK_BLUE);

    engine->DrawString(engine->ScreenWidth() / 4, 10, "Players:", olc::WHITE);
    engine->DrawString(engine->ScreenWidth() * 2 / 3, 10, "Rows:", olc::WHITE);

    for (unsigned int i = 0; i < 30; i++) {
        engine->DrawString(engine->ScreenWidth() / 5, 10 * i + 30, to_string(i + 1), olc::WHITE);

        if (i < size(serverCon.leaderboard)) {
            engine->DrawString(engine->ScreenWidth() / 4, 10 * i + 30, serverCon.leaderboard[to_string(i)]["playerName"], olc::WHITE);
            engine->DrawString(engine->ScreenWidth() * 2 / 3, 10 * i + 30, serverCon.leaderboard[to_string(i)]["score"], olc::WHITE);
        }
    }
}

void LeaderboardScene::Load() {
    serverCon.FetchLeaderboard();

    //Fetch highscores from server here
}

void LeaderboardScene::Unload() {

}
