#pragma once
#include "Scene.h"
#include "SceneManager.h"

class LeaderboardScene : public Scene{

    //Scene
    void Update(float fElapsedTime) override;
    void RenderGraphics() override;
    void Load() override;
    void Unload() override;
    using Scene::Scene;
};
