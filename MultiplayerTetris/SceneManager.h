#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Constants.h"
#include "Scene.h"
#include "ServerConnectionEmscripten.h"
#include <iostream>
#include <string>


class SceneManager{
private:
	Scene* currentScene;
	Scene* scenes[SCENES];

public:
	ServerConnectionEmscripten serverCon;
	struct dataStruct {
		std::string playerName = "";
		int bestSoloScore = 0;
	} data;

	void ChangeScene(int index);
	void Cycle(float fElapsedTime);
	void AddScene(int index, Scene* scene);
	SceneManager();
};
#endif