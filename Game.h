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

	SDL_Texture *LoadTexture(char *path);

private:
	void HandleEvents(); 
	void Update(); 
	void Draw(); 

	bool isRunning;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

	SDL_Texture *wallTexture = nullptr;
	SDL_Texture *groundTexture = nullptr;

	class LevelManager* levelManager;
	class Player *player;
	
};
