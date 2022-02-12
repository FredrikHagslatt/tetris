#include "SceneManager.h"

void SceneManager::ChangeScene(int index) {
	if (currentScene) {
		currentScene->Unload();
	}
	currentScene = scenes[index];
	currentScene->Load();
}

void SceneManager::AddScene(int index, Scene* scene) {
	scenes[index] = scene;
}


void SceneManager::Cycle(float fElapsedTime) {

	currentScene->Cycle(fElapsedTime);
}


SceneManager::SceneManager() {
	currentScene = nullptr;
}
