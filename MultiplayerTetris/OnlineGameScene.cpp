#include "OnlineGameScene.h"
#include "SceneManager.h"

void OnlineGameScene::Update(float fElapesedTime) {
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed) {
		sceneManager->ChangeScene("Menu");
	}
}

void OnlineGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2, "Under Development", olc::WHITE);
}

void OnlineGameScene::Load() {
}

void OnlineGameScene::Unload() {
}