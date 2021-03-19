#include "BasicControlsScene.h"
#include "SceneManager.h"

void BasicControlsScene::Update(float fElapsedTime) {
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed) {
		sceneManager->ChangeScene("Menu");
	}
}

void BasicControlsScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 - 10, "UP     -  Rotate Clockwise", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 00, "LEFT   -  Move Left", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 10, "RIGHT  -  Move Right", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 20, "DOWN   -  Soft Drop", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 3 + 30, "SPACE  -  Hard Drop", olc::WHITE);

}

void BasicControlsScene::Load() {

}

void BasicControlsScene::Unload() {

}
