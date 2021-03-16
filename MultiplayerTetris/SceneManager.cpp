#include "SceneManager.h"

void SceneManager::ChangeScene(string sceneName) {
	if (currentScene)
		currentScene->Unload();
	currentScene = scenes.find(sceneName)->second;
	currentScene->Load();
}

void SceneManager::AddScene(string sceneName, Scene* scene) {
	scenes.insert({ sceneName, scene });
}


void SceneManager::Cycle(float fElapsedTime) {

	currentScene->Cycle(fElapsedTime);
}


SceneManager::SceneManager() {
	currentScene = nullptr;
}
