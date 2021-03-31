#include "SplitScreenScoreScreenScene.h"
#include "SceneManager.h"

void SplitScreenScoreScreenScene::Update(float fElapsedTime) {
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed) {
		sceneManager->ChangeScene("Menu");
	}
}


void SplitScreenScoreScreenScene::RenderGraphics() {
	//Import deleted rows from engine->gameStats
	engine->Clear(olc::DARK_BLUE);
	int deletedRows = sceneManager->data.splitScreenPlayer1.deletedRows;

	if (sceneManager->data.splitScreenPlayer1.gameOver && sceneManager->data.splitScreenPlayer1.gameOver) {
		engine->DrawString(engine->ScreenWidth() * 2 / 5, engine->ScreenHeight() / 6, "Game is a draw!:", olc::WHITE, 2);
	}
	else if (sceneManager->data.splitScreenPlayer1.gameOver) {
		engine->DrawString(engine->ScreenWidth() * 2 / 5, engine->ScreenHeight() / 6, "Player 2 is the winner!:", olc::WHITE, 2);
	}
	else {
		engine->DrawString(engine->ScreenWidth() * 2 / 5, engine->ScreenHeight() / 6, "Player 1 is the winner!:", olc::WHITE, 2);
	}
	engine->DrawString(engine->ScreenWidth() / 2 - 15, engine->ScreenHeight() / 4, "Time played:", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() * 2 / 3 + 10, engine->ScreenHeight() / 4, to_string(sceneManager->data.timePlayed), olc::WHITE, 2);


	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2, "Player 1:", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2 + 20, "Deleted Rows:", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2 + 40, "Sent Rows:", olc::WHITE, 2);

	engine->DrawString(engine->ScreenWidth() * 3 / 4, engine->ScreenHeight() / 2, "Player 2:", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, engine->ScreenHeight() / 2 + 20, "Deleted Rows:", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, engine->ScreenHeight() / 2 + 40, "Sent Rows:", olc::WHITE, 2);



}


void SplitScreenScoreScreenScene::Load() {


}


void SplitScreenScoreScreenScene::Unload() {
}