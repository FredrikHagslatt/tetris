#include "SplitScreenGameScene.h"
#include "SceneManager.h"


int SplitScreenGameScene::GetX(int index) { return index % 10; }
int SplitScreenGameScene::GetY(int index) { return int(index / 10); }


void SplitScreenGameScene::ClearGame() {
	speedIncreaseTimer = 0;

	player1->ClearGame();
	player2->ClearGame();

	InitiateTetrominoes();
	InitiateTetrominoes();
}


void SplitScreenGameScene::InitiateTetrominoes() {
	player1->tetrominoes.clear();
	player2->tetrominoes.clear();

	Tetromino* newTetromino = &tetrominoTypes[rand() % 7];
	player1->activeTetromino = newTetromino;
	player2->activeTetromino = newTetromino;
	
	//Make list of tetrominoes to sync between all players in multiplayer

	for (int i = 0; i < 30; i++) {

		vector<Tetromino*> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L }; //Single bag randomizer
//			vector<Tetromino> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L, &I, &O, &T, &S, &Z, &J, &L }; //Double bag randomizer

		while (tetrominoVec.size()) {
			int index = rand() % tetrominoVec.size();
			player1->tetrominoes.push_back(tetrominoVec[index]);
			player2->tetrominoes.push_back(tetrominoVec[index]);
			tetrominoVec.erase(tetrominoVec.begin() + index);
		}
	}
}


void SplitScreenGameScene::SendRows(TetrisPlayer* sender, TetrisPlayer* recipient) {
	if (sender->newlyDeletedRows == 2) {
		recipient->AddRows(1);
		sender->sentRows += 1;
	}
	if (sender->newlyDeletedRows == 3) {
		recipient->AddRows(1);
		sender->sentRows += 1;
	}
	if (sender->newlyDeletedRows == 4) {
		recipient->AddRows(2);
		sender->sentRows += 2;
	}
}


void SplitScreenGameScene::EndGame() {

	sceneManager->data.player1.gameOver = player1->gameOver;
	sceneManager->data.player2.gameOver = player2->gameOver;

	sceneManager->data.player1.deletedRows = player1->deletedRows;
	sceneManager->data.player1.sentRows = player1->sentRows;

	sceneManager->data.player2.deletedRows = player2->deletedRows;
	sceneManager->data.player2.sentRows = player2->sentRows;

	sceneManager->data.timePlayed = timePlayed;
	sceneManager->ChangeScene(SPLITSCREENSCORESCREEN);
}


void SplitScreenGameScene::Update(float fElapsedTime) {
	timePlayed += fElapsedTime;

	speedIncreaseTimer += fElapsedTime;
	if (speedIncreaseTimer > 180.0f && downAutoSpeed > 0.3f) {
		speedIncreaseTimer = 0.0f;
		downAutoSpeed -= 0.1f;
		player1->SetDownAutoSpeed(downAutoSpeed);
		player2->SetDownAutoSpeed(downAutoSpeed);
	}
	player1->Controller(fElapsedTime);
	player2->Controller(fElapsedTime);

	SendRows(player1, player2);
	SendRows(player2, player1);

	player1->newlyDeletedRows = 0;
	player2->newlyDeletedRows = 0;

	if (player1->gameOver || player2->gameOver) { EndGame(); }

}


void SplitScreenGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	player1->DrawGrid();
	player2->DrawGrid();

	player1->DrawTetromino();
	player2->DrawTetromino();

	//player1 controls
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 - 5,		"Controls:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 15, "Left Arrow:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 25, "Move Left", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 40, "Right Arrow:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 50, "Move Right", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 65, "Down Arrow:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 75, "Soft Drop", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 90, "Up Arrow:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 100, "Rotate", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 110, "clockwise", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 125, "L:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 135, "Rotate", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 145, "counter", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 155, "clockwise", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 170, "K:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 + 180, "Hard Drop", olc::WHITE, 1);

	//player2 controls
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 - 5,		"Controls:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 15, "A:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 25, "Move Left", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 40, "D:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 50, "Move Right", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 65, "S:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 75, "Soft Drop", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 90, "W:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 100, "Rotate", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 110, "clockwise", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 125, "Q:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 135, "Rotate", olc::WHITE, 1);	
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 145, "counter", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 155, "clockwise", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 170, "TAB:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 + 180, "Hard Drop", olc::WHITE, 1);
}


void SplitScreenGameScene::Load() {
	player1 = new TetrisPlayer(engine, engine->ScreenHeight() / 10, engine->ScreenHeight() * 19 / 20, engine->ScreenWidth() * 7 / 20);
	player2 = new TetrisPlayer(engine, engine->ScreenHeight() / 10, engine->ScreenHeight() * 19 / 20, engine->ScreenWidth() * 13 / 20);

	timePlayed = 0.0f;
	speedIncreaseTimer = 0.0f;
	downAutoSpeed = 0.5f;

	player1->downAutoSpeed = downAutoSpeed;
	player2->downAutoSpeed = downAutoSpeed;

	engine->Clear(olc::DARK_BLUE);

	InitiateTetrominoes();
	InitiateTetrominoes();

	player1->SpawnNewTetromino();
	player2->SpawnNewTetromino();

	//player1 controls
	player1->buttonLeft = olc::A;
	player1->buttonRight = olc::D;
	player1->buttonSoftDrop = olc::S;
	player1->buttonHardDrop = olc::TAB;
	player1->buttonRotateClockwise = olc::W;
	player1->buttonRotateCounterClockwise = olc::Q;

	//player2 controls
	player2->buttonRotateCounterClockwise = olc::L;
	player2->buttonHardDrop = olc::K;
}


void SplitScreenGameScene::Unload() {
	delete player1;
	delete player2;
}