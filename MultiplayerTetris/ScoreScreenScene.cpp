#include "ScoreScreenScene.h"
#include "SceneManager.h"

void ScoreScreenScene::Update(float fElapsedTime) {
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed) {
		sceneManager->ChangeScene("Menu");
	}
}


void ScoreScreenScene::RenderGraphics() {
	//Import deleted rows from engine->gameStats
	engine->Clear(olc::DARK_BLUE);
	int deletedRows = sceneManager->data.deletedRows;

	int oldHighScore = 12;
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 - 10, "Your Score:", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 00, to_string(deletedRows), olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 20, "Your Best Score", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 30, to_string(oldHighScore), olc::WHITE);

	if (deletedRows > oldHighScore) {
		engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 50, "New Record!", olc::WHITE);
	}
}


void ScoreScreenScene::Load() {
}


void ScoreScreenScene::Unload() {
}