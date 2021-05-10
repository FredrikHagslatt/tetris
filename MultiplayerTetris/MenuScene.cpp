#include "MenuScene.h"
#include "SceneManager.h"

void MenuScene::Update(float fElapsedTime) {
	if (engine->GetKey(olc::UP).bPressed) { if (menuPos > 0) menuPos--; }
	if (engine->GetKey(olc::DOWN).bPressed) { if (menuPos < 3) menuPos++; }
	if (engine->GetKey(olc::ESCAPE).bPressed) { exit(EXIT_SUCCESS); }
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed) {
		switch (menuPos) {
		case 0: { sceneManager->ChangeScene(SOLOGAME); break; }
		case 1: { sceneManager->ChangeScene(SPLITSCREENGAME); break; }
		case 2: { sceneManager->ChangeScene(ONLINEGAME); break; }
		case 3: { sceneManager->ChangeScene(LEADERBOARD); break; }
		}
	}
}

void MenuScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2 - 40, "Solo - 3 Min Sprint", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2 - 20, "Local Multiplayer", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2, "Online Multiplayer", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2 + 20, "Solo Leaderboard", olc::WHITE, 2);
	engine->FillCircle(engine->ScreenWidth() / 4 - 30, engine->ScreenHeight() / 2 + (menuPos - 1) * 20 - 15, 6);
}

void MenuScene::Load() {

}

void MenuScene::Unload() {

}
