#pragma once
#include "Scene.h"
#include "Tetrominoes.h"
#include "TetrisPlayer.h"

class SoloGameScene : public Scene{

#define gridWidth 10
#define gridHeight 18

private:

	TetrisPlayer* player = nullptr;
	float downAutoSpeed = 0.5f;
	float speedIncreaseTimer = 0.0f;
	float gameTimer = 180.f;

	//Graphics
	int GetX(int index);
	int GetY(int index);
	void DrawPos(int board, int x, int y, olc::Pixel color);
	void DrawGrid(int board);
	void DrawTetromino(int x, int y);

	//GameCore
	void InitiateTetrominoes();
	void ClearGame();
	void EndGame();

	// Scene
	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;
};

