#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "Utils.h"

Game::Game() 
{
	Init();
	isRunning = true;
}

Game::~Game() {

}

bool Game::Init()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		printf("SDL failed to initialize Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("SOKOBAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if( !window) {
		printf("Window failed to initialize Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!renderer) {
		printf("Renderer failed to initialize Error: %s\n", SDL_GetError());
		return false;
	}

	levelManager = new LevelManager();
	levelManager->LoadLevel((char*)"level1.txt");
	
	return true;
}

void Game::GameLoop() {
	while(isRunning) {
		HandleEvents();
		Update();
		Draw();
	}
}

void Game::Update() {
}


void Game::Draw() {
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);
	SDL_Rect rect;
	
	for(int r = 0; r < TILE_ROWS; r++) {
		for (int c = 0; c < TILE_COLS; c++) {
			rect = { c * TILE_SIZE, r * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			/*if(levelManager->getChar(r, c) == 'x') {
				SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}*/
			switch(levelManager->levelMap[c][r]) {
			case 'X':
				SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
				break;
			default:
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				break;
			}
			SDL_RenderFillRect(renderer, &rect);

		}
	}

	SDL_RenderPresent(renderer);
}


