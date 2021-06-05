#include "SplitScreenGameScene.h"
#include "SceneManager.h"


int SplitScreenGameScene::GetX(int index) { return index % 10; }
int SplitScreenGameScene::GetY(int index) { return int(index / 10); }


void SplitScreenGameScene::DrawBoxString(int x, int y, std::string text, int scale = 1, olc::Pixel textColor = olc::WHITE, olc::Pixel backColor = olc::BLACK) {
	olc::vi2d textSize = engine->GetTextSize(text) * scale;
	engine->FillRect(x - 2, y - 2, textSize.x + 3, textSize.y + 3, backColor);
	engine->DrawString(x, y, text, textColor, scale);
}


void SplitScreenGameScene::DrawBoxString(int y, std::string text, int scale = 1, olc::Pixel textColor = olc::WHITE, olc::Pixel backColor = olc::BLACK) {
	int x = (engine->ScreenWidth() - engine->GetTextSize(text).x * scale) / 2;
	DrawBoxString(x, y, text, scale, textColor, backColor);
}


void SplitScreenGameScene::InitiateTetrominoes() {
	player1->tetrominoes.clear();
	player2->tetrominoes.clear();
	
	//Make list of tetrominoes to sync between all players in multiplayer
	std::vector<Tetromino*> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L }; //Single bag randomizer
//		vector<Tetromino> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L, &I, &O, &T, &S, &Z, &J, &L }; //Double bag randomizer

	std::default_random_engine rng = std::default_random_engine{ std::random_device{}() };
	for (int i = 0; i < 30; i++) {
		shuffle(begin(tetrominoVec), end(tetrominoVec), rng);
		player1->tetrominoes.insert(player1->tetrominoes.end(), tetrominoVec.begin(), tetrominoVec.end());
		player2->tetrominoes.insert(player2->tetrominoes.end(), tetrominoVec.begin(), tetrominoVec.end());
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


void SplitScreenGameScene::Update(float fElapsedTime) {

	if (!gameStarted) {
		if (engine->GetKey(olc::ENTER).bPressed) {
			gameStarted = true;
		}
		else if (engine->GetKey(olc::ESCAPE).bPressed) {
			sceneManager->ChangeScene(MENU);
		}
	}
	else if (gameFinished) {
		if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::ESCAPE).bPressed) {
			sceneManager->ChangeScene(MENU);
		}
	}
	else { //Game running
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

		if (player1->gameOver || player2->gameOver) { gameFinished = true; }
	}
}


void SplitScreenGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);
	player1->DrawGrid();
	player2->DrawGrid();

	player1->DrawTetromino();
	player2->DrawTetromino();

	//player1 controls
	engine->DrawString(engine->ScreenWidth() * 4 / 5, engine->ScreenHeight() / 5 - 5,  "Controls:", olc::WHITE, 1);
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
	engine->DrawString(engine->ScreenWidth() / 40, engine->ScreenHeight() / 5 - 5,	"Controls:", olc::WHITE, 1);
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

	if (!gameStarted) {
		DrawBoxString(engine->ScreenHeight() / 2 - 10, "Delete multiple rows simultaneously to add rows to your opponent");
		DrawBoxString(engine->ScreenHeight() / 2, "The last player remaining wins the game");
		DrawBoxString(engine->ScreenHeight() / 2 + 10, "Press ENTER to start the game");
	}
	else if (gameFinished) {
		if (player1->gameOver && player2->gameOver) {
			DrawBoxString(engine->ScreenHeight() / 3, "Game is a draw!:", 2);
		}
		else if (player1->gameOver) {
			DrawBoxString(engine->ScreenHeight() / 3, "Player 2 is the winner!", 2);
		}
		else {
			DrawBoxString(engine->ScreenHeight() / 3, "Player 1 is the winner!", 2);
		}
		DrawBoxString(engine->ScreenHeight() / 2 - 20, "Time played: " + std::to_string((int)timePlayed) + " seconds");
		DrawBoxString(engine->ScreenHeight() / 2, "Player:          1           2");
		DrawBoxString(engine->ScreenHeight() / 2 + 10, "Deleted Rows:    " 
			+ std::to_string(player1->deletedRows)
			+ "           " 
			+ std::to_string(player2->deletedRows));
		DrawBoxString(engine->ScreenHeight() / 2 + 20, "Sent Rows:       " 
			+ std::to_string(player1->sentRows)
			+ "           " 
			+ std::to_string(player2->sentRows));
	}
}


void SplitScreenGameScene::Load() {
	gameStarted = false;
	gameFinished = false;

	player1 = new TetrisPlayer(engine, engine->ScreenHeight() / 10, engine->ScreenHeight() * 19 / 20, engine->ScreenWidth() * 7 / 20);
	player2 = new TetrisPlayer(engine, engine->ScreenHeight() / 10, engine->ScreenHeight() * 19 / 20, engine->ScreenWidth() * 13 / 20);

	downAutoSpeed = 0.5f;
	speedIncreaseTimer = 0.0f;
	timePlayed = 0.0f;

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
