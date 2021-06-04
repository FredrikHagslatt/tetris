#ifndef ENTER_NAME_SCENE_H
#define ENTER_NAME_SCENE_H

#include "Scene.h"
class EnterNameScene : public Scene{
	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;
};
#endif