#pragma once
#include "olcPixelGameEngine.h"
#include "Tetrominoes.h"

class TetrisPlayer{

#define gridWidth 10
#define gridHeight 18

private:

	olc::PixelGameEngine* engine;
	string playerName = "";

	float downAutoTimer = 0.0f;
	float downAutoSpeed = 0.5f;
	float downHeldTimer = 0.0f;
	bool sideHeldStarted = 0.0f;
	float sideHeldTimer = 0.0f;
	int deletedRows = 0;
	int xPos = 5;
	int yPos = 5;
	int rotation = 0;
	int grid[gridWidth * gridHeight] = { 0 };

	int GetX(int index);
	int GetY(int index);
	int GetIndex(int x, int y);

	bool CheckCollisionRotation(int nextRotation);
	bool CheckCollisionLeft();
	bool CheckCollisionRight();
	bool CheckCollisionDown();
	void DeleteRow(int row);
	void CheckRowDeletion();
	void WriteTetrominoToGrid();

	void MoveLeft();
	void MoveRight();
	bool MoveDown(bool newSpawn);
	void RotateClockwise();
	void RotateCounterClockwise();
	void HardDrop();


public:
	bool gameOver = false;

	//grid placement
	int yStart;	int yEnd;
	int xStart;	int xEnd;
	int section;
	int edge;
	int tile;

	list<Tetromino*> tetrominoes; //Assigned by GameScene for sync in multiplayer
	Tetromino* activeTetromino = nullptr;

	void ClearGame();
	int* GetGrid();
	int GetXPos();
	int GetYPos();
	int GetRotation();
	int GetDeletedRows();
	void SetDownAutoSpeed(float _downAutoSpeed);
	void SpawnNewTetromino();

	void DrawTetromino();
	void DrawGrid();
	void Controller(float fElapsedTime);

	TetrisPlayer(olc::PixelGameEngine* _engine, int _yStart, int _yEnd, int _xStart);

};

