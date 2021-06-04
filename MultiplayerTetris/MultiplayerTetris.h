#ifndef MULTIPLAYER_TETRIS_H
#define MULTIPLAYER_TETRIS_H

#include "olcPixelGameEngine.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "LeaderboardScene.h"
#include "EnterNameScene.h"
#include "SoloGameScene.h"
#include "SplitScreenGameScene.h"
#include "OnlineGameScene.h"
//#include "SoloScoreScreenScene.h"
//#include "SplitScreenScoreScreenScene.h"
//#include "CreditsScene.h"

class MultiplayerTetris : public olc::PixelGameEngine {
public:
	SceneManager* sceneManager;
	MultiplayerTetris();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};
#endif