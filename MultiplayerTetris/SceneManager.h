#pragma once
#include "Scene.h"
#include <iostream>
#include <string>

using namespace std;

class SceneManager{
private:
	Scene* currentScene;
	unordered_map<string, Scene*> scenes;

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

	void ChangeScene(string sceneName);
	void Cycle(float fElapsedTime);
	void AddScene(string sceneName, Scene* scene);
	SceneManager();

};

