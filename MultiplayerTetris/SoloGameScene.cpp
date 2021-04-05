#include "SoloGameScene.h"
#include "SceneManager.h"

int SoloGameScene::GetX(int index) { return index % 10; }
int SoloGameScene::GetY(int index) { return int(index / 10); }


void SoloGameScene::ClearGame() {
	player->ClearGame();
	gameTimer = 180.0f;
	InitiateTetrominoes();
}


void SoloGameScene::InitiateTetrominoes() {
	player->tetrominoes.clear();
	player->activeTetromino = &tetrominoTypes[rand() % 7];
	//Make list of tetrominoes to sync between all players in multiplayer

	for (int i = 0; i < 30; i++) {

		vector<Tetromino*> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L }; //Single bag randomizer
//			vector<Tetromino> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L, &I, &O, &T, &S, &Z, &J, &L }; //Double bag randomizer

		while (tetrominoVec.size()) {
			int index = rand() % tetrominoVec.size();
			player->tetrominoes.push_back(tetrominoVec[index]);
			tetrominoVec.erase(tetrominoVec.begin() + index);
		}
	}
}


void SoloGameScene::EndGame() {
	sceneManager->data.player1.deletedRows = player->deletedRows;
	sceneManager->ChangeScene("SoloScoreScreen");
}


void SoloGameScene::Update(float fElapsedTime) {

	gameTimer -= fElapsedTime;
	if (gameTimer <= 0)
		player->gameOver = true;

	speedIncreaseTimer += fElapsedTime;
	if (speedIncreaseTimer > 90.0f && downAutoSpeed > 0.3f) {
		speedIncreaseTimer = 0.0f;
		downAutoSpeed -= 0.1f;
		player->downAutoSpeed = downAutoSpeed;
	}
	player->Controller(fElapsedTime);

	if (player->gameOver)
		EndGame();

}


void SoloGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);

	player->DrawGrid();
	player->DrawTetromino();

	engine->DrawString(engine->ScreenWidth() * 13 / 20, engine->ScreenHeight() / 10 + 5, "Deleted rows", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() * 13 / 20, engine->ScreenHeight() / 10 + 25, to_string(player->deletedRows), olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() * 13 / 20, engine->ScreenHeight() / 10 + 65, "Seconds: ", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() * 13 / 20, engine->ScreenHeight() / 10 + 85, to_string(gameTimer), olc::WHITE, 2);

	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 10 + 5, "<- Left", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 10 + 20, "-> Right", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 10 + 35, "v Soft drop", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 10 + 50, "Space Hard drop", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 10 + 65, "^ Rotate clockwise", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 10 + 80, "Z Rotate counter clockwise", olc::WHITE, 1);
}


void SoloGameScene::Load() {
	player = new TetrisPlayer(engine, engine->ScreenHeight() / 10, engine->ScreenHeight() * 19 / 20, engine->ScreenWidth() / 2);
	downAutoSpeed = 0.5f;
	speedIncreaseTimer = 0.0f;
	gameTimer = 180.0f;

	player->downAutoSpeed = downAutoSpeed;
	engine->Clear(olc::DARK_BLUE);
	InitiateTetrominoes();
	player->SpawnNewTetromino();
}


void SoloGameScene::Unload() {
	delete player;
}

