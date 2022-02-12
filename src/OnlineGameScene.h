#ifndef ONLINE_GAME_SCENE_H
#define ONLINE_GAME_SCENE_H
#include "Scene.h"
#include "Tetrominoes.h"
#include "TetrisPlayer.h"

class OnlineGameScene : public Scene {

private:
	void Update(float fElapsedTime) override;
	void RenderGraphics() override;
	void Load() override;
	void Unload() override;
	using Scene::Scene;
};
#endif