#include "SoloScoreScreenScene.h"
#include "SceneManager.h"

void SoloScoreScreenScene::Update(float fElapsedTime) {
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed)
		sceneManager->ChangeScene("Menu");
}


void SoloScoreScreenScene::RenderGraphics() {
	//Import deleted rows from engine->gameStats
	engine->Clear(olc::DARK_BLUE);

	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 - 10, "Your Score:", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 00, to_string(sceneManager->data.player1.deletedRows), olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 20, "Your Best Score", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 30, to_string(sceneManager->data.bestSoloScore), olc::WHITE);

	if (sceneManager->data.player1.deletedRows > sceneManager->data.bestSoloScore)
		engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 50, "New Record!", olc::WHITE);
}


void SoloScoreScreenScene::Load() {
}


void SoloScoreScreenScene::Unload() {
	if (sceneManager->data.player1.deletedRows > sceneManager->data.bestSoloScore)
		sceneManager->data.bestSoloScore = sceneManager->data.player1.deletedRows;
}