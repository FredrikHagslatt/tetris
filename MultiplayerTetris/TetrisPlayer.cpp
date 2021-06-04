#include "TetrisPlayer.h"

int TetrisPlayer::GetX(int index) { return index % 10; }
int TetrisPlayer::GetY(int index) { return int(index / 10); }
int TetrisPlayer::GetIndex(int x, int y) { return x + gridWidth * y; }
void TetrisPlayer::SetDownAutoSpeed(float _downAutoSpeed) { downAutoSpeed = _downAutoSpeed; }


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
	newlyDeletedRows = 0;
	for (int y = 0; y < gridHeight; y++) {
		bool rowFull = true;
		for (int x = 0; x < gridWidth; x++) {
			if (!grid[GetIndex(x, y)]) {
				rowFull = false;
			}
		}
		if (rowFull) {
			newlyDeletedRows++;
			DeleteRow(y);
		}
	}
	deletedRows += newlyDeletedRows;
}


void TetrisPlayer::WriteTetrominoToGrid() {
	for (int i = 0; i < 16; i++) {
		int index = GetIndex(xPos + activeTetromino->XOffset(i, rotation), yPos + activeTetromino->YOffset(i, rotation));
		if (activeTetromino->shape[i] && index >= 0) {
			grid[index] = activeTetromino->color;
		}
	}
}


void TetrisPlayer::AddRows(int rows) {
	if (rows == 0) {
		return;
	}

	//Move grid up
	for (int i = 0; i < gridWidth * gridHeight - rows * gridWidth; i++) {
		grid[i] = grid[i + rows * gridWidth];
	}

	//Fill row with blocks and gaps
	for (int i = 1; i <= rows; i++) {
		int ncolor = rand() % 7 + 1;
		for (int j = gridWidth * gridHeight - i * gridWidth; j < gridWidth * gridHeight - i * gridWidth + gridWidth; j++) {
			grid[j] = ncolor;
		}

		std::vector<int> indexes;
		for (int j = 0; j < gridWidth; j++)
			indexes.push_back(j);

		shuffle(begin(indexes), end(indexes), rng);

		int gaps = rand() % 2 + 1;
		for (int j = 0; j < gaps; j++) {
			grid[gridWidth * gridHeight - i * gridWidth + indexes.back()] = 0;
			indexes.pop_back();
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
			gameOver = true;
			break;
		}
	}
}


void TetrisPlayer::MoveLeft() {
	if (!CheckCollisionLeft()) { xPos--; }
}


void TetrisPlayer::MoveRight() {
	if (!CheckCollisionRight()) { xPos++; }
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
	if (MoveDown(false)) { HardDrop(); }
}


void TetrisPlayer::Controller(float fElapsedTime) {

	if (engine->GetKey(buttonSoftDrop).bHeld) {
		downHeldTimer = downHeldTimer + fElapsedTime;
		if (downHeldTimer >= 0.03) {
			MoveDown(false);
			downHeldTimer = 0.0;
		}
	}

	if (engine->GetKey(buttonLeft).bHeld) {
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

	if (engine->GetKey(buttonRight).bHeld) {
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

	if (engine->GetKey(buttonLeft).bPressed) { MoveLeft(); sideHeldStarted = false; sideHeldTimer = 0.0f; }
	if (engine->GetKey(buttonRight).bPressed) { MoveRight(); sideHeldStarted = false; sideHeldTimer = 0.0f; }
	if (engine->GetKey(buttonSoftDrop).bPressed) { MoveDown(false); downHeldTimer = 0.0f; }
	if (engine->GetKey(buttonHardDrop).bPressed) { HardDrop(); }
	if (engine->GetKey(buttonRotateClockwise).bPressed) { RotateClockwise(); }
	if (engine->GetKey(buttonRotateCounterClockwise).bPressed) { RotateCounterClockwise(); }
	if (engine->GetKey(buttonPause).bPressed) {	gameOver = true; } // pause menu will be implemented later

	downAutoTimer = downAutoTimer + fElapsedTime;
	if (downAutoTimer >= downAutoSpeed) {
		MoveDown(false);
	}
}


void TetrisPlayer::DrawTetromino() {
	for (int i = 0; i < 16; i++) {
		if (activeTetromino->shape[i]) {
			engine->FillRect(xStart + edge + section * (xPos + activeTetromino->XOffset(i, rotation)),
				yStart + edge + section * (yPos + activeTetromino->YOffset(i, rotation)),
				tile,
				tile,
				colors[activeTetromino->color]);
		}
	}
}


void TetrisPlayer::DrawGrid() {
	for (int i = 0; i < gridWidth * gridHeight; i++) {
		engine->FillRect(xStart + edge + section * GetX(i),
			yStart + edge + section * GetY(i),
			tile,
			tile,
			colors[grid[i]]);
	}
}


TetrisPlayer::TetrisPlayer(olc::PixelGameEngine* _engine, int _yStart, int _yEnd, int _xCenter) {
	engine = _engine;
	yStart = _yStart;
	yEnd = _yEnd;
	section = (yEnd - yStart) / gridHeight;
	xStart = _xCenter - section * gridWidth / 2;
	xEnd = _xCenter + section * gridWidth / 2;

	edge = section * 1 / 8;
	tile = section * 7 / 8;
}
