#pragma once

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

using namespace std;


class MultiplayerTetris : public olc::PixelGameEngine {
public:
	SceneManager* sceneManager;
	MultiplayerTetris();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};