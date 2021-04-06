#pragma once
#include "Scene.h"
class SoloScoreScreenScene : public Scene {

	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;
};
