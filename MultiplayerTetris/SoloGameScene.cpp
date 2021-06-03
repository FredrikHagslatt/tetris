#include "SoloGameScene.h"
#include "SceneManager.h"

int SoloGameScene::GetX(int index) { return index % 10; }
int SoloGameScene::GetY(int index) { return int(index / 10); }


void SoloGameScene::DrawBoxString(int x, int y, string text, int scale = 1, olc::Pixel textColor = olc::WHITE, olc::Pixel backColor = olc::BLACK) {
	olc::vi2d textSize = engine->GetTextSize(text) * scale;
	engine->FillRect(x - 2, y - 2, textSize.x + 3, textSize.y + 3, backColor);
	engine->DrawString(x, y, text, textColor, scale);
}


void SoloGameScene::DrawBoxString(int y, string text, int scale = 1, olc::Pixel textColor = olc::WHITE, olc::Pixel backColor = olc::BLACK) {
	int x = (engine->ScreenWidth() - engine->GetTextSize(text).x * scale) / 2;
	DrawBoxString(x, y, text, scale, textColor, backColor);
}


void SoloGameScene::InitiateTetrominoes() {
	player->tetrominoes.clear();
	player->activeTetromino = &tetrominoTypes[rand() % 7];
	//Make list of tetrominoes to sync between all players in multiplayer

	for (int i = 0; i < 30; i++) {
		vector<Tetromino*> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L }; //Single bag randomizer
//			vector<Tetromino> tetrominoVec{ &I, &O, &T, &S, &Z, &J, &L, &I, &O, &T, &S, &Z, &J, &L }; //Double bag randomizer

		while (tetrominoVec.size()) {
			int index = rand() % tetrominoVec.size();
			player->tetrominoes.push_back(tetrominoVec[index]);
			tetrominoVec.erase(tetrominoVec.begin() + index);
		}
	}
}


void SoloGameScene::Update(float fElapsedTime) {
	if (!gameStarted) {
		if (engine->GetKey(olc::ENTER).bPressed) {
			gameStarted = true;
		}
		else if (engine->GetKey(olc::ESCAPE).bPressed) {
			sceneManager->ChangeScene(MENU);
		}
	}
	else if (gameFinished) {
		if (engine->GetKey(olc::ENTER).bPressed || engine->GetKey(olc::SPACE).bPressed || engine->GetKey(olc::ESCAPE).bPressed) {
			sceneManager->ChangeScene(MENU);
		}
	}
	else {

		gameTimer -= fElapsedTime;
		if (gameTimer <= 0) {
			player->gameOver = true;
		}

		speedIncreaseTimer += fElapsedTime;
		if (speedIncreaseTimer > 90.0f && downAutoSpeed > 0.3f) {
			speedIncreaseTimer = 0.0f;
			downAutoSpeed -= 0.1f;
			player->downAutoSpeed = downAutoSpeed;
		}
		player->Controller(fElapsedTime);

		if (player->gameOver) { 

            sceneManager->serverCon.RefreshSoloScore(); 
            oldScore = sceneManager->serverCon.soloScore;
            
            if (sceneManager->serverCon.soloScore < player->deletedRows) {
                sceneManager->serverCon.soloScore = player->deletedRows;
		        sceneManager->serverCon.PostHighscore(sceneManager->data.playerName, player->deletedRows);
	        }

            gameFinished = true;
            if (gameTimer < 0.0f) {
				gameTimer = 0.0f;
			}
		}
	}
}


void SoloGameScene::RenderGraphics() {
	engine->Clear(olc::DARK_BLUE);

	player->DrawGrid();
	player->DrawTetromino();

	engine->DrawString(engine->ScreenWidth() * 13 / 20, engine->ScreenHeight() / 10 + 15, "Deleted rows", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 13 / 20, engine->ScreenHeight() / 10 + 25, to_string(player->deletedRows), olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() * 13 / 20, engine->ScreenHeight() / 10 + 45, "Seconds: ", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() * 13 / 20, engine->ScreenHeight() / 10 + 55, to_string(gameTimer), olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 15, "Controls:",	olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 35, "Left Arrow:",	olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 45, "Move Left",	olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 65, "Right Arrow:", olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 75, "Move Right",	olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 95, "Down Arrow:",	olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 105, "Soft Drop",	olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 125, "Up Arrow:",	olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 135, "Rotate",		olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 145, "clockwise",	olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 165, "Z:",			olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 175, "Rotate",		olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 185, "counter",		olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 195, "clockwise",	olc::WHITE, 1);

	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 215, "Spacebar:",	olc::WHITE, 1);
	engine->DrawString(engine->ScreenWidth() / 5, engine->ScreenHeight() / 10 + 225, "Hard Drop",	olc::WHITE, 1);

	if (!gameStarted) {
		DrawBoxString(engine->ScreenHeight() / 2 - 10, "Delete as many rows as possible before the time runs out");
		DrawBoxString(engine->ScreenHeight() / 2, "Press ENTER to start the game");
	}
	else if (gameFinished) {
		DrawBoxString(engine->ScreenHeight() / 2 - 10, "Your Score: " + to_string(player->deletedRows));
		DrawBoxString(engine->ScreenHeight() / 2, "Your Best Score: " + to_string(oldScore));


		if (player->deletedRows > oldScore){
			DrawBoxString(engine->ScreenHeight() / 2 + 10, "New Record!");
        }
    }
}


void SoloGameScene::Load() {
    sceneManager->serverCon.FetchSoloScore(sceneManager->data.playerName);
    player = new TetrisPlayer(engine, engine->ScreenHeight() / 10, engine->ScreenHeight() * 19 / 20, engine->ScreenWidth() / 2);

	gameStarted = false;
	gameFinished = false;

	downAutoSpeed = 0.5f;
	speedIncreaseTimer = 0.0f;
	gameTimer = 180.0f;

	player->downAutoSpeed = downAutoSpeed;
	engine->Clear(olc::DARK_BLUE);
	InitiateTetrominoes();
	player->SpawnNewTetromino();
}


void SoloGameScene::Unload() {
	delete player;
}
