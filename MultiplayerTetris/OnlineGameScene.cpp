#include "OnlineGameScene.h"
#include "SceneManager.h"


void OnlineGameScene::Update(float fElapsedTime) {
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed)
		sceneManager->ChangeScene("Menu");
}


void OnlineGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() * 1 / 5, engine->ScreenHeight() / 2, "Work in progress", olc::WHITE, 3);
}

void OnlineGameScene::Load() {

}

void OnlineGameScene::Unload() {
}