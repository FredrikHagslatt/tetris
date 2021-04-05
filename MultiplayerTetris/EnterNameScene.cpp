#include "EnterNameScene.h"
#include "SceneManager.h"

void EnterNameScene::Update(float fElapsedTime) {
	if (sceneManager->data.player1.playerName.size() < 12) {
		if (engine->GetKey(olc::A).bPressed) { sceneManager->data.player1.playerName += "A"; }
		if (engine->GetKey(olc::B).bPressed) { sceneManager->data.player1.playerName += "B"; }
		if (engine->GetKey(olc::C).bPressed) { sceneManager->data.player1.playerName += "C"; }
		if (engine->GetKey(olc::D).bPressed) { sceneManager->data.player1.playerName += "D"; }
		if (engine->GetKey(olc::E).bPressed) { sceneManager->data.player1.playerName += "E"; }
		if (engine->GetKey(olc::F).bPressed) { sceneManager->data.player1.playerName += "F"; }
		if (engine->GetKey(olc::G).bPressed) { sceneManager->data.player1.playerName += "G"; }
		if (engine->GetKey(olc::H).bPressed) { sceneManager->data.player1.playerName += "H"; }
		if (engine->GetKey(olc::I).bPressed) { sceneManager->data.player1.playerName += "I"; }
		if (engine->GetKey(olc::J).bPressed) { sceneManager->data.player1.playerName += "J"; }
		if (engine->GetKey(olc::K).bPressed) { sceneManager->data.player1.playerName += "K"; }
		if (engine->GetKey(olc::L).bPressed) { sceneManager->data.player1.playerName += "L"; }
		if (engine->GetKey(olc::M).bPressed) { sceneManager->data.player1.playerName += "M"; }
		if (engine->GetKey(olc::N).bPressed) { sceneManager->data.player1.playerName += "N"; }
		if (engine->GetKey(olc::O).bPressed) { sceneManager->data.player1.playerName += "O"; }
		if (engine->GetKey(olc::P).bPressed) { sceneManager->data.player1.playerName += "P"; }
		if (engine->GetKey(olc::Q).bPressed) { sceneManager->data.player1.playerName += "Q"; }
		if (engine->GetKey(olc::R).bPressed) { sceneManager->data.player1.playerName += "R"; }
		if (engine->GetKey(olc::S).bPressed) { sceneManager->data.player1.playerName += "S"; }
		if (engine->GetKey(olc::T).bPressed) { sceneManager->data.player1.playerName += "T"; }
		if (engine->GetKey(olc::U).bPressed) { sceneManager->data.player1.playerName += "U"; }
		if (engine->GetKey(olc::V).bPressed) { sceneManager->data.player1.playerName += "V"; }
		if (engine->GetKey(olc::W).bPressed) { sceneManager->data.player1.playerName += "W"; }
		if (engine->GetKey(olc::X).bPressed) { sceneManager->data.player1.playerName += "X"; }
		if (engine->GetKey(olc::Y).bPressed) { sceneManager->data.player1.playerName += "Y"; }
		if (engine->GetKey(olc::Z).bPressed) { sceneManager->data.player1.playerName += "Z"; }
	}

	if (engine->GetKey(olc::BACK).bPressed && sceneManager->data.player1.playerName.size() > 0) {
		sceneManager->data.player1.playerName.erase(sceneManager->data.player1.playerName.end() - 1);
	}

	if (engine->GetKey(olc::ENTER).bPressed && sceneManager->data.player1.playerName.size() > 0) {
		sceneManager->ChangeScene("Menu");
	}

}

void EnterNameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	engine->DrawString(engine->ScreenWidth() / 3, engine->ScreenHeight() / 2 - 10, "Please enter nickname:", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 7, engine->ScreenHeight() / 2 + 10, sceneManager->data.player1.playerName, olc::WHITE);
}

void EnterNameScene::Load() {

}

void EnterNameScene::Unload() {

}

