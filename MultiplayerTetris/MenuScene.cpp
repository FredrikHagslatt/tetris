#include "MenuScene.h"
#include "SceneManager.h"

void MenuScene::Update(float fElapsedTime) {
	if (engine->GetKey(olc::UP).bPressed) { if (menuPos > 0) menuPos--; }
	if (engine->GetKey(olc::DOWN).bPressed) { if (menuPos < 6) menuPos++; }
	if (engine->GetKey(olc::ESCAPE).bPressed) { exit(EXIT_SUCCESS); }
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed) {
		switch (menuPos) {
		case 0: { sceneManager->ChangeScene("SoloGame"); break; }
		case 1: { sceneManager->ChangeScene("SplitScreenGame"); break; }
		case 2: { sceneManager->ChangeScene("OnlineGame"); break; }
		case 3: { sceneManager->ChangeScene("HighScores"); break; }
		case 4: { exit(EXIT_SUCCESS); break; }
		}
	}
}

void MenuScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 - 50, "Solo - 3 Min Sprint", olc::WHITE, 3);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 - 20, "Local Multiplayer", olc::WHITE, 3);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 10, "Online Multiplayer", olc::WHITE, 3);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 40, "Highscores", olc::WHITE, 3);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 70, "Exit", olc::WHITE, 3);
	engine->FillCircle(engine->ScreenWidth() / 3 - 30, engine->ScreenHeight() / 3 + (menuPos - 1) * 30 - 10, 9);
}

void MenuScene::Load() {

}

void MenuScene::Unload() {

}
