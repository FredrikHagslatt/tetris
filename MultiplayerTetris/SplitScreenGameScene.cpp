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
	if (sender->newlyDeletedRows == 2)
		recipient->AddRows(1);
	if (sender->newlyDeletedRows == 3)
		recipient->AddRows(2);
	if (sender->newlyDeletedRows == 4)
		recipient->AddRows(3);
}


void SplitScreenGameScene::EndGame() {
	sceneManager->ChangeScene("ScoreScreen");
}


void SplitScreenGameScene::Update(float fElapsedTime) {
	if (player1->gameOver || player2->gameOver){ EndGame();	}

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
}


void SplitScreenGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	player1->DrawGrid();
	player2->DrawGrid();

	player1->DrawTetromino();
	player2->DrawTetromino();

	//player1 controls
	engine->DrawString(engine->ScreenWidth() * 4 / 5 - 30, engine->ScreenHeight() / 5 - 5,		"Controls:", olc::WHITE, 2);
	engine->DrawString(engine->ScreenWidth() * 4 / 5 - 30, engine->ScreenHeight() / 5 + 15 * 1, "Left              = Left Arrow", olc::WHITE, 1.5);
	engine->DrawString(engine->ScreenWidth() * 4 / 5 - 30, engine->ScreenHeight() / 5 + 15 * 2, "Right             = Right Arrow", olc::WHITE, 1.5);
	engine->DrawString(engine->ScreenWidth() * 4 / 5 - 30, engine->ScreenHeight() / 5 + 15 * 3, "Soft Drop         = Down Arrow", olc::WHITE, 1.5);
	engine->DrawString(engine->ScreenWidth() * 4 / 5 - 30, engine->ScreenHeight() / 5 + 15 * 4, "Clockwise         = Up Arrow", olc::WHITE, 1.5);
	engine->DrawString(engine->ScreenWidth() * 4 / 5 - 30, engine->ScreenHeight() / 5 + 15 * 5, "Counter Clockwise = L", olc::WHITE, 1.5);
	engine->DrawString(engine->ScreenWidth() * 4 / 5 - 30, engine->ScreenHeight() / 5 + 15 * 6, "Hard Drop         = K", olc::WHITE, 1.5);

	//player2 controls
	engine->DrawString(30, engine->ScreenHeight() / 5 - 5,		"Controls:", olc::WHITE, 2);
	engine->DrawString(30, engine->ScreenHeight() / 5 + 15 * 1, "Left              = A", olc::WHITE, 1.5);
	engine->DrawString(30, engine->ScreenHeight() / 5 + 15 * 2, "Right             = D", olc::WHITE, 1.5);
	engine->DrawString(30, engine->ScreenHeight() / 5 + 15 * 3, "Soft Drop         = S", olc::WHITE, 1.5);
	engine->DrawString(30, engine->ScreenHeight() / 5 + 15 * 4, "Clockwise         = W", olc::WHITE, 1.5);
	engine->DrawString(30, engine->ScreenHeight() / 5 + 15 * 5, "Counter Clockwise = Q", olc::WHITE, 1.5);
	engine->DrawString(30, engine->ScreenHeight() / 5 + 15 * 6, "Hard Drop         = TAB", olc::WHITE, 1.5);
}


void SplitScreenGameScene::Load() {
	player1 = new TetrisPlayer(engine, 100, 700, 250);
	player2 = new TetrisPlayer(engine, 100, 700, 650);

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
}