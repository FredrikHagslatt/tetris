#include "MultiplayerTetris.h"

MultiplayerTetris::MultiplayerTetris() {
	sAppName = "Freppan's Tetris";
}

bool MultiplayerTetris::OnUserCreate(){
	srand(time(NULL));
	sceneManager = new SceneManager();
	sceneManager->AddScene(MENU, new MenuScene(this, sceneManager));
	sceneManager->AddScene(ENTERNAME, new EnterNameScene(this, sceneManager));
	sceneManager->AddScene(LEADERBOARD, new LeaderboardScene(this, sceneManager));

	sceneManager->AddScene(SOLOGAME, new SoloGameScene(this, sceneManager));
	sceneManager->AddScene(SPLITSCREENGAME, new SplitScreenGameScene(this, sceneManager));
	sceneManager->AddScene(ONLINEGAME, new OnlineGameScene(this, sceneManager));
//	sceneManager->AddScene(CREDITS, new GameScene(this, sceneManager));

	sceneManager->ChangeScene(ENTERNAME);

	return true;
}

bool MultiplayerTetris::OnUserUpdate(float fElapsedTime){
	sceneManager->Cycle(fElapsedTime);
	return true;
}
