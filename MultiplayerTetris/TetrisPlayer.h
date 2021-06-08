#ifndef TETRIS_PLAYER_H
#define TETRIS_PLAYER_H

#include "Constants.h"
#include "olcPixelGameEngine.h"
#include "Tetrominoes.h"
#include <algorithm>
#include <random>


class TetrisPlayer{

private:

	std::default_random_engine rng = std::default_random_engine{ std::random_device{}() };

	olc::PixelGameEngine* engine;
	std::string playerName = "";

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
	int yStart;
	int xStart;
	int section;
	int edge;
	int tile;

	//NextTetrominoPanel placement
	bool showNextTetrominoPanel = false;
	int xPanel; 
	int yPanel;

	//default controls
	olc::Key buttonLeft = olc::LEFT;
	olc::Key buttonRight = olc::RIGHT;
	olc::Key buttonSoftDrop = olc::DOWN;
	olc::Key buttonHardDrop = olc::SPACE;
	olc::Key buttonPause = olc::ESCAPE;
	olc::Key buttonRotateClockwise = olc::UP;
	olc::Key buttonRotateCounterClockwise = olc::Z;

	std::list<Tetromino*> tetrominoes; //Assigned by GameScene for sync in multiplayer
	Tetromino* activeTetromino = nullptr;
	Tetromino* nextTetromino = nullptr;

	void SpawnNewTetromino();
	void AddRows(int rows);

	void DrawTetromino(int x, int y, Tetromino* tetromino);
	void DrawActiveTetromino();
	void DrawGrid();
	void Controller(float fElapsedTime);

	void ActivateNextTetrominoPanel(int xCenter, int y);
	TetrisPlayer(olc::PixelGameEngine* _engine, int _xCenter, int _yStart, int _yEnd);

};
#endif
