#include "MultiplayerTetris.h"

MultiplayerTetris::MultiplayerTetris() {
	sAppName = "Freppan's Tetris";
}

bool MultiplayerTetris::OnUserCreate(){
	srand(time(NULL));

	sceneManager = new SceneManager();
	sceneManager->AddScene("Menu", new MenuScene(this, sceneManager));
	//sceneManager->AddScene("EnterName", new EnterNameScene(this, sceneManager));
	//sceneManager->AddScene("HighScores", new HighScoresScene(this, sceneManager));
	sceneManager->AddScene("SoloScoreScreen", new SoloScoreScreenScene(this, sceneManager));
	sceneManager->AddScene("SplitScreenScoreScreen", new SplitScreenScoreScreenScene(this, sceneManager));

	//	sceneManager->AddScene("Credits", new GameScene(this, sceneManager));

	sceneManager->AddScene("SoloGame", new SoloGameScene(this, sceneManager));
	sceneManager->AddScene("SplitScreenGame", new SplitScreenGameScene(this, sceneManager));
	sceneManager->AddScene("OnlineGame", new OnlineGameScene(this, sceneManager));

	sceneManager->ChangeScene("Menu");
	return true;
}

bool MultiplayerTetris::OnUserUpdate(float fElapsedTime){
	sceneManager->Cycle(fElapsedTime);
	return true;
}
