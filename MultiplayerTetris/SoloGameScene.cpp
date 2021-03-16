#include "SoloGameScene.h"
#include "SceneManager.h"

int SoloGameScene::GetX(int index) { return index % 10; }
int SoloGameScene::GetY(int index) { return int(index / 10); }


void SoloGameScene::ClearGame() {
	player->ClearGame();
	gameTimer = 180.0f;
	InitiateTetrominoes();
}

void SoloGameScene::DrawPos(int board, int x, int y, olc::Pixel color) {
	int xPixel = 0;
	int yPixel = 0;
	int width = 0;
	int height = 0;
	int yOffset = 2 * 36;

	switch (board) {
	case 0: { xPixel = 2 * (1 + 7 * x); yPixel = 2 * (1 + 7 * y) + yOffset; width = 2 * 6; height = 2 * 6; break; }
	case 1: { xPixel = 2 * (1 + 9 * x + 71); yPixel = 2 * (1 + 9 * y); width = 2 * 8; height = 2 * 8; break; }
	case 2: { xPixel = 2 * (1 + 7 * x + 71 + 91); yPixel = 2 * (1 + 7 * y) + yOffset; width = 2 * 6; height = 2 * 6; break; }

	}
	engine->FillRect(xPixel, yPixel, width, height, color);
}


void SoloGameScene::DrawGrid(int board) {
	int* grid = player->GetGrid();
	for (int i = 0; i < gridWidth * gridHeight; i++) {
		switch (board) {
//		case 0: {DrawPos(board, GetX(i), GetY(i), colors[opponentGrids[i]]); break; }
		case 1: {DrawPos(board, GetX(i), GetY(i), colors[grid[i]]); break; }
//		case 2: {DrawPos(board, GetX(i), GetY(i), colors[opponentGrids[gridWidth * gridHeight + i]]); break; }
		}
	}
}


void SoloGameScene::DrawTetromino(int x, int y) {
	for (int i = 0; i < 16; i++) {
		if (player->activeTetromino->shape[i]) {
			DrawPos(1, x + player->activeTetromino->XOffset(i, player->GetRotation()), y + player->activeTetromino->YOffset(i, player->GetRotation()), colors[player->activeTetromino->color]);

		}
	}
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
	sceneManager->data.deletedRows = player->GetDeletedRows();
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
	DrawGrid(1);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 10, "Deleted", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 20, "rows: ", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 30, to_string(player->GetDeletedRows()), olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 40, "Seconds: ", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 50, to_string(gameTimer), olc::WHITE);
	DrawTetromino(player->GetXPos(), player->GetYPos());

}


void SoloGameScene::Load() {
	player = new TetrisPlayer(engine);
	player->SetDownAutoSpeed(downAutoSpeed);
	engine->Clear(olc::DARK_BLUE);
	InitiateTetrominoes();
	player->SpawnNewTetromino();
}


void SoloGameScene::Unload() {
}

