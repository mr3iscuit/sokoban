#pragma once

#include "Utils.h"
#include "LevelManager.h"

class Game {
public:
	Game();
	~Game();
	bool Init();
	void GameLoop();
	void ShutDown();

private:
	void HandleEvents() {}
	void Update(); 
	void Draw(); 

	bool isRunning;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

	class LevelManager* levelManager;
	
};
