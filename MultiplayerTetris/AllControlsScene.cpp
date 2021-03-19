#include "AllControlsScene.h"
#include "SceneManager.h"

void AllControlsScene::Update(float fElapsedTime) {
	if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed) {
		sceneManager->ChangeScene("Menu");
	}
}

void AllControlsScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 - 60, "Right Handed:", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 - 50, "UP     -  Rotate Clockwise", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 - 40, "LEFT   -  Move Left", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 - 30, "RIGHT  -  Move Right", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 - 20, "DOWN   -  Soft Drop", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 - 10, "SPACE  -  Hard Drop", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 00, "Z      -  Rotate Counter Clockwise", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 10, "X      -  Rotate Clockwise", olc::WHITE);

	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 30, "Left Handed:", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 40, "W      -  Rotate Clockwise", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 50, "A      -  Move Left", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 60, "S      -  Soft Drop", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 70, "D      -  Move Right", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 80, "ENTER  -  Hard Drop", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 90, "N      -  Rotate Counter Clockwise", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 100, "M      -  Rotate Clockwise", olc::WHITE);

	engine->DrawString(engine->ScreenWidth() / 4, engine->ScreenHeight() / 3 + 130, "ESC    -  Exit Game", olc::WHITE);
}

void AllControlsScene::Load() {

}

void AllControlsScene::Unload() {

}
