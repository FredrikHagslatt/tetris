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

public:

	struct dataStruct {
		string playerName = "";
		int bestSoloScore = 0;
	} data;

	void ChangeScene(int index);
	void Cycle(float fElapsedTime);
	void AddScene(int index, Scene* scene);
	SceneManager();

};

