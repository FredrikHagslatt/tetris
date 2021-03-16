#include "MenuScene.h"
#include "SceneManager.h"

void MenuScene::Update(float fElapesedTime) {
	if (engine->GetKey(olc::UP).bPressed) { if (menuPos > 0) menuPos--; }
	if (engine->GetKey(olc::DOWN).bPressed) { if (menuPos < 5) menuPos++; }
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed) {
		switch (menuPos) {
		case 0: {sceneManager->ChangeScene("SoloGame"); break; }
		case 1: {sceneManager->ChangeScene("SplitScreenGame"); break; }
		case 2: {sceneManager->ChangeScene("OnlineGame"); break; }
		case 3: {sceneManager->ChangeScene("HighScores"); break; }
		case 4: {sceneManager->ChangeScene("BasicControls"); break; }
		case 5: {sceneManager->ChangeScene("AllControls"); break; }
		}
	}
}

void MenuScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 - 10, "Solo - 3 Min Sprint", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3, "Local Multiplayer", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 10, "Online Multiplayer", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 20, "Highscores", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 30, "Basic Controlls", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 40, "All Controlls", olc::WHITE);
	engine->FillCircle(engine->ScreenWidth() / 3 - 10, engine->ScreenHeight() / 3 + (menuPos - 1) * 10 + 2, 3);

}

void MenuScene::Load() {

}

void MenuScene::Unload() {

}
