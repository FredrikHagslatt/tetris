#pragma once
#include "Scene.h"
class ScoreScreenScene : public Scene {

	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;
};

