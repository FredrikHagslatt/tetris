#include "SplitScreenGameScene.h"
#include "SceneManager.h"


int SplitScreenGameScene::GetX(int index) { return index % 10; }
int SplitScreenGameScene::GetY(int index) { return int(index / 10); }


void SplitScreenGameScene::ClearGame() {
	player1->ClearGame();
	player2->ClearGame();

	gameTimer = 180.0f;
	InitiateTetrominoes(player1);
	InitiateTetrominoes(player2);
}


void SplitScreenGameScene::InitiateTetrominoes(TetrisPlayer* player) {
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


void SplitScreenGameScene::EndGame() {
	sceneManager->ChangeScene("ScoreScreen");
}


void SplitScreenGameScene::Update(float fElapsedTime) {
	if (player1->gameOver || player2->gameOver) {
		EndGame();
	}

	gameTimer -= fElapsedTime;
	if (gameTimer < 0) { EndGame(); }

	speedIncreaseTimer += fElapsedTime;
	if (speedIncreaseTimer > 90.0f && downAutoSpeed > 0.3f) {
		speedIncreaseTimer = 0.0f;
		downAutoSpeed -= 0.1f;
		player1->SetDownAutoSpeed(downAutoSpeed);
		player2->SetDownAutoSpeed(downAutoSpeed);
	}
	player1->Controller(fElapsedTime);
	player2->Controller(fElapsedTime);
}


void SplitScreenGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	player1->DrawGrid();
	player2->DrawGrid();

	player2->DrawTetromino();

	engine->DrawString(engine->ScreenWidth() * 3 / 4, 10, "Deleted", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 20, "rows: ", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 30, to_string(player2->GetDeletedRows()), olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 40, "Seconds: ", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 50, to_string(gameTimer), olc::WHITE);
}


void SplitScreenGameScene::Load() {
	player1 = new TetrisPlayer(engine, 100, 700, 200);
	player2 = new TetrisPlayer(engine, 100, 700, 700);

	player1->SetDownAutoSpeed(downAutoSpeed);
	player2->SetDownAutoSpeed(downAutoSpeed);

	engine->Clear(olc::DARK_BLUE);

	InitiateTetrominoes(player1);
	InitiateTetrominoes(player2);

	player1->SpawnNewTetromino();
	player2->SpawnNewTetromino();
}


void SplitScreenGameScene::Unload() {
}