#pragma once
#include "Scene.h"
#include "Tetrominoes.h"
#include "TetrisPlayer.h"

class SoloGameScene : public Scene{

private:
	bool gameStarted = false;
	bool gameFinished = false;

	TetrisPlayer* player = nullptr;
	float downAutoSpeed = 0.5f;
	float speedIncreaseTimer = 0.0f;
	float gameTimer = 180.f;

	//Graphics
	void DrawBoxString(int x, int y, string text, int scale, olc::Pixel textColor, olc::Pixel backColor);
	void DrawBoxString(int y, string text, int scale, olc::Pixel textColor, olc::Pixel backColor);
	int GetX(int index);
	int GetY(int index);

	//GameCore
	void InitiateTetrominoes();

	// Scene
	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;
};

