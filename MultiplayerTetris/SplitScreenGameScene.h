#pragma once
#include "Scene.h"
#include "Tetrominoes.h"
#include "TetrisPlayer.h"


class SplitScreenGameScene : public Scene {

private:
	bool gameStarted = false;
	bool gameFinished = false;

	TetrisPlayer* player1 = nullptr;
	TetrisPlayer* player2 = nullptr;

	float downAutoSpeed = 0.5f;
	float speedIncreaseTimer = 0.0f;
	float timePlayed = 0.0f;

	//Graphics
	void DrawBoxString(int x, int y, string text, int scale, olc::Pixel textColor, olc::Pixel backColor);
	void DrawBoxString(int y, string text, int scale, olc::Pixel textColor, olc::Pixel backColor);
	int GetX(int index);
	int GetY(int index);

	//GameCore
	void InitiateTetrominoes();
	void SendRows(TetrisPlayer* sender, TetrisPlayer* recipient);

	//Scene
public:
	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;

};

