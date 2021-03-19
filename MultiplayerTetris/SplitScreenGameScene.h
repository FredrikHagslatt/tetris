#pragma once
#include "Scene.h"
#include "Tetrominoes.h"
#include "TetrisPlayer.h"


class SplitScreenGameScene : public Scene {


#define gridWidth 10
#define gridHeight 18

private:

	TetrisPlayer* player1 = nullptr;
	TetrisPlayer* player2 = nullptr;

	float downAutoSpeed = 0.5f;
	float speedIncreaseTimer = 0.0f;
	float gameTimer = 180.f;

	//Graphics
	int GetX(int index);
	int GetY(int index);

	//GameCore
	void InitiateTetrominoes();
	void ClearGame();
	void EndGame();

	//Scene
public:
	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;

};

