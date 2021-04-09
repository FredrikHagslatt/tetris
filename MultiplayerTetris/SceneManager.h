#pragma once
#include "Constants.h"
#include "Scene.h"
#include <iostream>
#include <string>

using namespace std;

class SceneManager{
private:
	Scene* currentScene;
	Scene* scenes[SCENES];

	struct playerStruct {
		string playerName = "";
		int deletedRows = 0;
		int sentRows = 0;
		bool gameOver = false;
	};

public:

	struct dataStruct {
		int bestSoloScore = 0;
		float timePlayed = 0.0f;
		playerStruct player1;
		playerStruct player2;
	} data;

	void ChangeScene(int index);
	void Cycle(float fElapsedTime);
	void AddScene(int index, Scene* scene);
	SceneManager();

};

