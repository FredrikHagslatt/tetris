#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "ServerConnectionEmscripten.h"

class LeaderboardScene : public Scene{

    ServerConnectionEmscripten serverCon;

    //Scene
    void Update(float fElapsedTime) override;
    void RenderGraphics() override;
    void Load() override;
    void Unload() override;
    using Scene::Scene;

};

