#include "EnterNameScene.h"
#include "SceneManager.h"

void EnterNameScene::Update(float fElapsedTime) {
	if (sceneManager->data.playerName.size() < 12) {
		if (engine->GetKey(olc::A).bPressed) { sceneManager->data.playerName += "A"; }
		if (engine->GetKey(olc::B).bPressed) { sceneManager->data.playerName += "B"; }
		if (engine->GetKey(olc::C).bPressed) { sceneManager->data.playerName += "C"; }
		if (engine->GetKey(olc::D).bPressed) { sceneManager->data.playerName += "D"; }
		if (engine->GetKey(olc::E).bPressed) { sceneManager->data.playerName += "E"; }
		if (engine->GetKey(olc::F).bPressed) { sceneManager->data.playerName += "F"; }
		if (engine->GetKey(olc::G).bPressed) { sceneManager->data.playerName += "G"; }
		if (engine->GetKey(olc::H).bPressed) { sceneManager->data.playerName += "H"; }
		if (engine->GetKey(olc::I).bPressed) { sceneManager->data.playerName += "I"; }
		if (engine->GetKey(olc::J).bPressed) { sceneManager->data.playerName += "J"; }
		if (engine->GetKey(olc::K).bPressed) { sceneManager->data.playerName += "K"; }
		if (engine->GetKey(olc::L).bPressed) { sceneManager->data.playerName += "L"; }
		if (engine->GetKey(olc::M).bPressed) { sceneManager->data.playerName += "M"; }
		if (engine->GetKey(olc::N).bPressed) { sceneManager->data.playerName += "N"; }
		if (engine->GetKey(olc::O).bPressed) { sceneManager->data.playerName += "O"; }
		if (engine->GetKey(olc::P).bPressed) { sceneManager->data.playerName += "P"; }
		if (engine->GetKey(olc::Q).bPressed) { sceneManager->data.playerName += "Q"; }
		if (engine->GetKey(olc::R).bPressed) { sceneManager->data.playerName += "R"; }
		if (engine->GetKey(olc::S).bPressed) { sceneManager->data.playerName += "S"; }
		if (engine->GetKey(olc::T).bPressed) { sceneManager->data.playerName += "T"; }
		if (engine->GetKey(olc::U).bPressed) { sceneManager->data.playerName += "U"; }
		if (engine->GetKey(olc::V).bPressed) { sceneManager->data.playerName += "V"; }
		if (engine->GetKey(olc::W).bPressed) { sceneManager->data.playerName += "W"; }
		if (engine->GetKey(olc::X).bPressed) { sceneManager->data.playerName += "X"; }
		if (engine->GetKey(olc::Y).bPressed) { sceneManager->data.playerName += "Y"; }
		if (engine->GetKey(olc::Z).bPressed) { sceneManager->data.playerName += "Z"; }
	}

	if (engine->GetKey(olc::BACK).bPressed && sceneManager->data.playerName.size() > 0) {
		sceneManager->data.playerName.erase(sceneManager->data.playerName.end() - 1);
	}

	if (engine->GetKey(olc::ENTER).bPressed && sceneManager->data.playerName.size() > 0) {
		sceneManager->ChangeScene(MENU);
	}

}

void EnterNameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 2 - 10, "Please enter nickname:", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 7, engine->ScreenHeight() / 2 + 10, sceneManager->data.playerName, olc::WHITE);
}

void EnterNameScene::Load() {

}

void EnterNameScene::Unload() {

}

