#pragma once
#include "olcPixelGameEngine.h"
#include <string>
using namespace std;

class SceneManager;

class Scene{

public:
	SceneManager* sceneManager;
	olc::PixelGameEngine* engine;
	virtual void Update(float fElapsedTime) = 0;
	virtual void RenderGraphics() = 0;
	virtual void Load() = 0; //Preparation for music etc
	virtual void Unload() = 0;
	void Cycle(float fElapsedTime);
	Scene(olc::PixelGameEngine* _engine, SceneManager* _sceneManager);
};