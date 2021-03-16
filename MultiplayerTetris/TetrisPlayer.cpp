#include "TetrisPlayer.h"

int* TetrisPlayer::GetGrid() { return grid; }
int TetrisPlayer::GetXPos() { return xPos; }
int TetrisPlayer::GetYPos() { return yPos; }
int TetrisPlayer::GetRotation() { return rotation; }
int TetrisPlayer::GetDeletedRows() { return deletedRows; }

int TetrisPlayer::GetIndex(int x, int y) { return x + gridWidth * y; }

void TetrisPlayer::SetDownAutoSpeed(float _downAutoSpeed) { downAutoSpeed = _downAutoSpeed; }


void TetrisPlayer::ClearGame() {
	deletedRows = 0;
	for (int i = 0; i < gridWidth * gridHeight; i++) {
		grid[i] = 0;
	}
}


bool TetrisPlayer::CheckCollisionRotation(int nextRotation) {
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


bool TetrisPlayer::CheckCollisionLeft() {
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


bool TetrisPlayer::CheckCollisionRight() {
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


bool TetrisPlayer::CheckCollisionDown() {
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


void TetrisPlayer::DeleteRow(int row) {
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


void TetrisPlayer::CheckRowDeletion() {
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


void TetrisPlayer::WriteTetrominoToGrid() {
	for (int i = 0; i < 16; i++) {
		int index = GetIndex(xPos + activeTetromino->XOffset(i, rotation), yPos + activeTetromino->YOffset(i, rotation));
		if (activeTetromino->shape[i] && index >= 0) {
			grid[index] = activeTetromino->color;
		}
	}
}


void TetrisPlayer::SpawnNewTetromino() {
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
			gameOver = true;
			//				oldHighScore = cloudConnection.GetHighScore();
			//				cloudConnection.SendSingleplayerRecord();
			//			}
			//			gameState.EndGame();
			break;
		}
	}
}


void TetrisPlayer::MoveLeft() {
	if (!CheckCollisionLeft()) {
		xPos--;
	}
}


void TetrisPlayer::MoveRight() {
	if (!CheckCollisionRight()) {
		xPos++;
	}
}


bool TetrisPlayer::MoveDown(bool newSpawn) {
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


void TetrisPlayer::RotateClockwise() {
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


void TetrisPlayer::RotateCounterClockwise() {
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


void TetrisPlayer::HardDrop() {
	if (MoveDown(false))
		HardDrop();
}


void TetrisPlayer::Controller(float fElapsedTime) {

	if (engine->GetKey(olc::ESCAPE).bPressed) {
		gameOver = true; //Pause menu will be implemented later
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

	downAutoTimer = downAutoTimer + fElapsedTime;
	if (downAutoTimer >= downAutoSpeed) {
		MoveDown(false);
	}

}


TetrisPlayer::TetrisPlayer(olc::PixelGameEngine* _engine) {
	engine = _engine;
}
