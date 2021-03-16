#include "SplitScreenGameScene.h"
#include "SceneManager.h"

void SplitScreenGameScene::Update(float fElapesedTime) {
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed) {
		sceneManager->ChangeScene("Menu");
	}
}

void SplitScreenGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 2, "Under Development", olc::WHITE);
}

void SplitScreenGameScene::Load() {
}

void SplitScreenGameScene::Unload() {
}