#pragma once
#include <vector>

#include "Utils.h"
#include "LevelManager.h"

class Game {
public:
	Game();
	~Game();
	bool Init();
	void GameLoop();
	void ShutDown();
	bool hitWall(int x, int y);
	bool hitBox(int x, int y);
	bool pushBox(int moveX, int moveY, int pX, int pY);

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
	SDL_Texture *goldTexture = nullptr;
	SDL_Texture *boxTexture = nullptr;

	class LevelManager* levelManager;
	class Player *player;
};
