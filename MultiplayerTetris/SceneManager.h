#pragma once
#include "Scene.h"
#include <iostream>
#include <string>

using namespace std;

class SceneManager{
private:
	Scene* currentScene;
	unordered_map<string, Scene*> scenes;

public:

	struct dataStruct {
		string playerName = "";
		int deletedRows = 0;
	} data;

	void ChangeScene(string sceneName);
	void Cycle(float fElapsedTime);
	void AddScene(string sceneName, Scene* scene);
	SceneManager();

};

