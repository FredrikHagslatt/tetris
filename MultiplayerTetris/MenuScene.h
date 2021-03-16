#pragma once
#include "Scene.h"
class MenuScene : public Scene{

	//MenuController
	int menuPos = 0;

	//Scene
	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;

};

