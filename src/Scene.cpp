#include "Scene.h"
#include "SceneManager.h"


void Scene::Cycle(float fElapsedTime) {
	RenderGraphics();
	Update(fElapsedTime);
}


Scene::Scene(olc::PixelGameEngine* _engine, SceneManager* _sceneManager) {
	engine = _engine;
	sceneManager = _sceneManager;
}

