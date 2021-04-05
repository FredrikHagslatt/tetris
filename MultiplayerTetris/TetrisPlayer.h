#pragma once
#include "olcPixelGameEngine.h"
#include "Tetrominoes.h"
#include <algorithm>
#include <random>

using namespace std;

class TetrisPlayer{

#define gridWidth 10
#define gridHeight 18

private:

	default_random_engine rng = default_random_engine{ random_device{}() };

	olc::PixelGameEngine* engine;
	string playerName = "";

	int grid[gridWidth * gridHeight] = { 0 };
	float downAutoTimer = 0.0f;
	float downHeldTimer = 0.0f;
	bool sideHeldStarted = 0.0f;
	float sideHeldTimer = 0.0f;
	int xPos = 5;
	int yPos = 5;
	int rotation = 0;

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
	int newlyDeletedRows = 0;
	float downAutoSpeed = 0.5f;
	int deletedRows = 0;
	int sentRows = 0;

	//grid placement
	int yStart;	int yEnd;
	int xStart;	int xEnd;
	int section;
	int edge;
	int tile;

	//default controls
	olc::Key buttonLeft = olc::LEFT;
	olc::Key buttonRight = olc::RIGHT;
	olc::Key buttonSoftDrop = olc::DOWN;
	olc::Key buttonHardDrop = olc::SPACE;
	olc::Key buttonPause = olc::ESCAPE;
	olc::Key buttonRotateClockwise = olc::UP;
	olc::Key buttonRotateCounterClockwise = olc::Z;


	list<Tetromino*> tetrominoes; //Assigned by GameScene for sync in multiplayer
	Tetromino* activeTetromino = nullptr;

	void ClearGame();
	void SetDownAutoSpeed(float _downAutoSpeed);
	void SpawnNewTetromino();
	void AddRows(int rows);

	void DrawTetromino();
	void DrawGrid();
	void Controller(float fElapsedTime);

	TetrisPlayer(olc::PixelGameEngine* _engine, int _yStart, int _yEnd, int _xCenter);

};

