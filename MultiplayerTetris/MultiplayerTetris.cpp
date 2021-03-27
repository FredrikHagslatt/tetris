#include "MultiplayerTetris.h"

MultiplayerTetris::MultiplayerTetris() {
	sAppName = "Freppan's Tetris";
}

bool MultiplayerTetris::OnUserCreate(){
	srand(time(NULL));

	sceneManager = new SceneManager();
	sceneManager->AddScene("EnterName", new EnterNameScene(this, sceneManager));
	sceneManager->AddScene("Menu", new MenuScene(this, sceneManager));
	sceneManager->AddScene("HighScores", new HighScoresScene(this, sceneManager));
	sceneManager->AddScene("ScoreScreen", new ScoreScreenScene(this, sceneManager));
	sceneManager->AddScene("BasicControls", new BasicControlsScene(this, sceneManager));
	sceneManager->AddScene("AllControls", new AllControlsScene(this, sceneManager));
//	sceneManager->AddScene("Credits", new GameScene(this, sceneManager));

	sceneManager->AddScene("SoloGame", new SoloGameScene(this, sceneManager));
	sceneManager->AddScene("SplitScreenGame", new SplitScreenGameScene(this, sceneManager));
	sceneManager->AddScene("OnlineGame", new OnlineGameScene(this, sceneManager));

	sceneManager->ChangeScene("EnterName");

	return true;
}

bool MultiplayerTetris::OnUserUpdate(float fElapsedTime){
	sceneManager->Cycle(fElapsedTime);
	return true;
}
