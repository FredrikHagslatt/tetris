#include "SplitScreenScoreScreenScene.h"
#include "SceneManager.h"

void SplitScreenScoreScreenScene::Update(float fElapsedTime) {
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed)
		sceneManager->ChangeScene(MENU);
}


void SplitScreenScoreScreenScene::RenderGraphics() {
	//Import deleted rows from engine->gameStats
	engine->Clear(olc::DARK_BLUE);

	if (sceneManager->data.player1.gameOver && sceneManager->data.player2.gameOver) {
		engine->DrawString(engine->ScreenWidth() * 3 / 10, engine->ScreenHeight() / 6, "Game is a draw!:", olc::WHITE, 2);
	}
	else if (sceneManager->data.player1.gameOver) {
		engine->DrawString(engine->ScreenWidth() * 1 / 5, engine->ScreenHeight() / 6, "Player 2 is the winner!", olc::WHITE, 2);
	}
	else {
		engine->DrawString(engine->ScreenWidth() * 1 / 5, engine->ScreenHeight() / 6, "Player 1 is the winner!", olc::WHITE, 2);
	}
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 4, "Time played:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 2, engine->ScreenHeight() / 4, to_string((int)sceneManager->data.timePlayed), olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 11 / 20, engine->ScreenHeight() / 4, "seconds", olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2 + 20, "Deleted Rows:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2 + 40, "Sent Rows:", olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() * 9 / 20, engine->ScreenHeight() / 2, "Player 1", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 12 / 20, engine->ScreenHeight() / 2, "Player 2", olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() * 19 / 40, engine->ScreenHeight() / 2 + 20, to_string(sceneManager->data.player1.deletedRows), olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 25 / 40, engine->ScreenHeight() / 2 + 20, to_string(sceneManager->data.player2.deletedRows), olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() * 19 / 40, engine->ScreenHeight() / 2 + 40, to_string(sceneManager->data.player1.sentRows), olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 25 / 40, engine->ScreenHeight() / 2 + 40, to_string(sceneManager->data.player2.sentRows), olc::WHITE, 1);
}


void SplitScreenScoreScreenScene::Load() {


}


void SplitScreenScoreScreenScene::Unload() {
}