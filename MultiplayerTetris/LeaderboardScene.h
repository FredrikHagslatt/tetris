#ifndef LEADERBOARD_SCENE_H
#define LEADERBOARD_SCENE_H

#include "Scene.h"
#include "SceneManager.h"

class LeaderboardScene : public Scene{
    void Update(float fElapsedTime) override;
    void RenderGraphics() override;
    void Load() override;
    void Unload() override;
    using Scene::Scene;
};
#endif