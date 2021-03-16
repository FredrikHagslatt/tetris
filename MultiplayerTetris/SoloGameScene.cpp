#include "SoloGameScene.h"
#include "SceneManager.h"

int SoloGameScene::GetX(int index) { return index % 10; }
int SoloGameScene::GetY(int index) { return int(index / 10); }
int SoloGameScene::GetIndex(int x, int y) { return x + gridWidth * y; }

void SoloGameScene::ResetGameTimer() {
	deletedRows = 0;
	gameTimer = 180.0f;
}


void SoloGameScene::ClearGame() {
	ResetGameTimer();
	for (int i = 0; i < gridWidth * gridHeight; i++) {
		grid[i] = 0;
	}
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
		if (activeTetromino->shape[i]) {
			DrawPos(1, x + activeTetromino->XOffset(i, rotation), y + activeTetromino->YOffset(i, rotation), colors[activeTetromino->color]);

		}
	}
}


bool SoloGameScene::CheckCollisionRotation(int nextRotation) {
	for (int i = 0; i < 16; i++) {
		if (activeTetromino->shape[i]) {
			if (xPos + activeTetromino->XOffset(i, nextRotation) < 0 || xPos + activeTetromino->XOffset(i, nextRotation) >= gridWidth) {
				return true;
			}
			else if (grid[GetIndex(xPos + activeTetromino->XOffset(i, nextRotation), yPos + activeTetromino->YOffset(i, nextRotation))]) {
				return true;
			}
		}
	}
	return false;
}

bool SoloGameScene::CheckCollisionLeft() {
	for (int i = 0; i < 16; i++) {
		if (activeTetromino->shape[i]) {
			if (xPos + activeTetromino->XOffset(i, rotation) - 1 < 0) {
				return true;
			}
			else if (grid[GetIndex(xPos + activeTetromino->XOffset(i, rotation) - 1, yPos + activeTetromino->YOffset(i, rotation))]) {
				return true;
			}
		}
	}
	return false;
}


bool SoloGameScene::CheckCollisionRight() {
	for (int i = 0; i < 16; i++) {
		if (activeTetromino->shape[i]) {
			if (xPos + activeTetromino->XOffset(i, rotation) + 1 >= gridWidth) {
				return true;
			}
			else if (grid[GetIndex(xPos + activeTetromino->XOffset(i, rotation) + 1, yPos + activeTetromino->YOffset(i, rotation))]) {
				return true;
			}
		}
	}
	return false;
}


bool SoloGameScene::CheckCollisionDown() {
	for (int i = 0; i < 16; i++) {
		if (activeTetromino->shape[i]) {
			if (GetIndex(xPos + activeTetromino->XOffset(i, rotation), yPos + activeTetromino->YOffset(i, rotation) + 1) >= 0) {
				if (yPos + activeTetromino->YOffset(i, rotation) + 1 >= gridHeight) { //If under the grid
					return true;
				}
				else if (grid[GetIndex(xPos + activeTetromino->XOffset(i, rotation), yPos + activeTetromino->YOffset(i, rotation) + 1)]) { //If next Y is taken
					return true;
				}
			}
		}
	}
	return false;
}

void SoloGameScene::DeleteRow(int row) {
	for (int x = 0; x < gridWidth; x++) { //Delete row
		grid[GetIndex(x, row)] = 0;
	}
	for (int index = row * gridWidth + gridWidth - 1; index >= gridWidth; index--) { //Move upper rows down
		grid[index] = grid[index - gridWidth];
	}
	for (int index = 0; index < gridWidth; index++) { //Clear top row
		grid[index] = 0;
	}
}


void SoloGameScene::CheckRowDeletion() {
	for (int y = 0; y < gridHeight; y++) {
		bool rowFull = true;
		for (int x = 0; x < gridWidth; x++) {
			if (!grid[GetIndex(x, y)]) {
				rowFull = false;
			}
		}
		if (rowFull) {
			deletedRows++;
			DeleteRow(y);
		}
	}
}

void SoloGameScene::InitiateTetrominoes() {
	tetrominoes.clear();
	activeTetromino = &tetrominoTypes[rand() % 7];
	//Make list of tetrominoes to sync between all players

	for (int i = 0; i < 30; i++) {

		vector<Tetromino*> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L }; //Single bag randomizer
//			vector<Tetromino> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L, &I, &O, &T, &S, &Z, &J, &L }; //Double bag randomizer

		while (tetrominoVec.size()) {
			int index = rand() % tetrominoVec.size();
			tetrominoes.push_back(tetrominoVec[index]);
			tetrominoVec.erase(tetrominoVec.begin() + index);
		}
	}
}


void SoloGameScene::WriteTetrominoToGrid() {
	for (int i = 0; i < 16; i++) {
		int index = GetIndex(xPos + activeTetromino->XOffset(i, rotation), yPos + activeTetromino->YOffset(i, rotation));
		if (activeTetromino->shape[i] && index >= 0) {
			grid[index] = activeTetromino->color;
		}
	}
}


void SoloGameScene::SpawnNewTetromino() {
	xPos = int(gridWidth / 2 - 2);
	yPos = -4;
	rotation = 0;
	activeTetromino = tetrominoes.front();
	tetrominoes.pop_front();
	tetrominoes.push_back(activeTetromino);
	while (yPos) {
		if (!MoveDown(true)) {
//			if (gameState.multiplayerGame) {
//				cloudConnection.SendMultiplayerInfo();
//			}
//			else { //singleplayerGame
			EndGame();
//				oldHighScore = cloudConnection.GetHighScore();
//				cloudConnection.SendSingleplayerRecord();
//			}
//			gameState.EndGame();
			break;
		}
	}
}


void SoloGameScene::EndGame() {
	sceneManager->data.deletedRows = deletedRows;
	sceneManager->ChangeScene("ScoreScreen");
}


void SoloGameScene::MoveLeft() {
	if (!CheckCollisionLeft()) {
		xPos--;
	}
}


void SoloGameScene::MoveRight() {
	if (!CheckCollisionRight()) {
		xPos++;
	}
}


bool SoloGameScene::MoveDown(bool newSpawn) {
	downAutoTimer = 0;
	if (!CheckCollisionDown()) {
		yPos++;
		return true;
	}
	else {
		WriteTetrominoToGrid();
		CheckRowDeletion();

		if (!newSpawn) {
			SpawnNewTetromino();
		}
		return false;
	}
}


void SoloGameScene::RotateClockwise() {
	int nextRotation;
	if (rotation < activeTetromino->rotations - 1) {
		nextRotation = rotation + 1;
	}
	else {
		nextRotation = 0;
	}
	if (!CheckCollisionRotation(nextRotation)) {
		rotation = nextRotation;
	}
}


void SoloGameScene::RotateCounterClockwise() {
	int nextRotation;
	if (rotation > 0) {
		nextRotation = rotation - 1;
	}
	else {
		nextRotation = activeTetromino->rotations - 1;
	}
	if (!CheckCollisionRotation(nextRotation)) {
		rotation = nextRotation;
	}
}


void SoloGameScene::HardDrop() {
	if (MoveDown(false))
		HardDrop();
}


void SoloGameScene::Controller(float fElapsedTime) {

	if (engine->GetKey(olc::ESCAPE).bPressed) {
		EndGame();
	}

	if (engine->GetKey(olc::UP).bPressed || engine->GetKey(olc::W).bPressed || engine->GetKey(olc::X).bPressed || engine->GetKey(olc::M).bPressed) {
		RotateClockwise();
	}

	if (engine->GetKey(olc::Z).bPressed || engine->GetKey(olc::N).bPressed) {
		RotateCounterClockwise();
	}

	if (engine->GetKey(olc::DOWN).bHeld || engine->GetKey(olc::S).bHeld) {
		downHeldTimer = downHeldTimer + fElapsedTime;
		if (downHeldTimer >= 0.03) {
			MoveDown(false);
			downHeldTimer = 0.0;
		}
	}

	if (engine->GetKey(olc::LEFT).bHeld || engine->GetKey(olc::A).bHeld) {
		if (sideHeldStarted) {
			sideHeldTimer = sideHeldTimer + fElapsedTime;
			if (sideHeldTimer >= 0.05) {
				MoveLeft();
				sideHeldTimer = 0.0;
			}
		}
		else if (sideHeldTimer > 0.12) {
			sideHeldStarted = true;
			sideHeldTimer = 0.0f;
		}
		else {
			sideHeldTimer = sideHeldTimer + fElapsedTime;
		}
	}

	if (engine->GetKey(olc::RIGHT).bHeld || engine->GetKey(olc::D).bHeld) {
		if (sideHeldStarted) {
			sideHeldTimer = sideHeldTimer + fElapsedTime;
			if (sideHeldTimer >= 0.05) {
				MoveRight();
				sideHeldTimer = 0.0;
			}
		}
		else if (sideHeldTimer > 0.12) {
			sideHeldStarted = true;
			sideHeldTimer = 0.0f;
		}
		else {
			sideHeldTimer = sideHeldTimer + fElapsedTime;
		}
	}

	if (engine->GetKey(olc::DOWN).bPressed || engine->GetKey(olc::S).bPressed) { MoveDown(false); downHeldTimer = 0.0f; }
	if (engine->GetKey(olc::LEFT).bPressed || engine->GetKey(olc::A).bPressed) { MoveLeft(); sideHeldStarted = false; sideHeldTimer = 0.0f; }
	if (engine->GetKey(olc::RIGHT).bPressed || engine->GetKey(olc::D).bPressed) { MoveRight(); sideHeldStarted = false; sideHeldTimer = 0.0f; }
	if (engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ENTER).bPressed) { HardDrop(); }
}


void SoloGameScene::Update(float fElapsedTime) {
	gameTimer -= fElapsedTime;
	if (gameTimer < 0) { EndGame(); }

	speedIncreaseTimer += fElapsedTime;
	if (speedIncreaseTimer > 90.0f && downAutoSpeed > 0.3f) {
		speedIncreaseTimer = 0.0f;
		downAutoSpeed -= 0.1f;
	}

	Controller(fElapsedTime);

	downAutoTimer = downAutoTimer + fElapsedTime;
	if (downAutoTimer >= downAutoSpeed) {
		MoveDown(false);
	}

}


void SoloGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	DrawGrid(1);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 10, "Deleted", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 20, "rows: ", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 30, to_string(deletedRows), olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 40, "Seconds: ", olc::WHITE);
	engine->DrawString(engine->ScreenWidth() * 3 / 4, 50, to_string(gameTimer), olc::WHITE);
	DrawTetromino(xPos, yPos);

}


void SoloGameScene::Load() {
	engine->Clear(olc::DARK_BLUE);

	InitiateTetrominoes();
	SpawnNewTetromino();

}


void SoloGameScene::Unload() {
}

