#pragma once
#include "Scene.h"
#include "Tetrominoes.h"

class SoloGameScene : public Scene{

#define gridWidth 10
#define gridHeight 18

private:
	string playerName = "";

	float downHeldTimer = 0.0f;
	bool sideHeldStarted = 0.0f;
	float sideHeldTimer = 0.0f;
	float downAutoTimer = 0.0f;
	float downAutoSpeed = 0.5f;
	float speedIncreaseTimer = 0.0f;
	int deletedRows = 0;
	float gameTimer = 180.f;

	int xPos = 5;
	int yPos = 5;
	int rotation = 0;
	Tetromino* activeTetromino = nullptr;
	list<Tetromino*> tetrominoes;

	int grid[gridWidth * gridHeight] = { 0 };

	//GameCore
	void ResetGameTimer();
	int GetX(int index);
	int GetY(int index);
	int GetIndex(int x, int y);
	void DrawPos(int board, int x, int y, olc::Pixel color);
	void DrawGrid(int board);
	void DrawTetromino(int x, int y);
	bool CheckCollisionRotation(int nextRotation);
	bool CheckCollisionLeft();
	bool CheckCollisionRight();
	bool CheckCollisionDown();
	void DeleteRow(int row);
	void CheckRowDeletion();
	void InitiateTetrominoes();
	void WriteTetrominoToGrid();
	void SpawnNewTetromino();
	void ClearGame();
	void EndGame();

	//Controller
	void MoveLeft();
	void MoveRight();
	bool MoveDown(bool newSpawn);
	void RotateClockwise();
	void RotateCounterClockwise();
	void HardDrop();
	void Controller(float fElapsedTime);

	// Scene
	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;
};

