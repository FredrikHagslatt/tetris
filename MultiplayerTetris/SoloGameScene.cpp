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
	sceneManager->data.deletedRows = player->deletedRows;
	sceneManager->ChangeScene("ScoreScreen");
}


void SoloGameScene::Update(float fElapsedTime) {
	if (player->gameOver) {
		EndGame();
	}

	gameTimer -= fElapsedTime;
	if (gameTimer < 0) { EndGame(); }

	speedIncreaseTimer += fElapsedTime;
	if (speedIncreaseTimer > 90.0f && downAutoSpeed > 0.3f) {
		speedIncreaseTimer = 0.0f;
		downAutoSpeed -= 0.1f;
		player->SetDownAutoSpeed(downAutoSpeed);
	}
	player->Controller(fElapsedTime);
}


void SoloGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);

	player->DrawGrid();
	player->DrawTetromino();

	engine->DrawString(engine->ScreenWidth() * 3 / 4, 10, "Deleted", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 20, "rows: ", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 30, to_string(player->deletedRows), olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 40, "Seconds: ", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 50, to_string(gameTimer), olc::WHITE);
}


void SoloGameScene::Load() {
	player = new TetrisPlayer(engine, 100, 700, 200);
	player->SetDownAutoSpeed(downAutoSpeed);
	engine->Clear(olc::DARK_BLUE);
	InitiateTetrominoes();
	player->SpawnNewTetromino();
}


void SoloGameScene::Unload() {
}

