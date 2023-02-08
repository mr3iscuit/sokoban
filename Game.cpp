#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include "Utils.h"
#include "Player.h"

Game::Game() 
{
	Init();
	isRunning = true;
}

bool Game::Init()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		printf("SDL failed to initialize Error: %s\n", SDL_GetError());
		return false;
	}

	if(IMG_Init(IMG_INIT_PNG) == 0) {
		printf("SDL image failed to initialize Error: %s\n", IMG_GetError());
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

	wallTexture = LoadTexture((char*)"assets/wall.png");
	groundTexture = LoadTexture((char*)"assets/ground.png");
	goldTexture = LoadTexture((char*)"assets/gold.png");
	boxTexture = LoadTexture((char*)"assets/box.png");
	

	player = new Player(this);
	int c = 0, r = 0;
	for(r = 0; r < TILE_ROWS; r++)
		for(c = 0; c < TILE_COLS; c++) 
			switch(levelManager->levelMap[c][r]) {
			case 'P':
				player->move(c, r);
				break;
			default:
				break;
			}
	
	return true;
}

bool Game::hitWall(int x, int y)
{
	return levelManager->levelMap[x][y] == 'X';
}

bool Game::hitBox(int x, int y)
{
	return levelManager->levelMap[x][y] == 'B';
}

bool Game::pushBox(int moveX, int moveY, int pX, int pY) 
{
	int newBoxX = pX + moveX;
	int newBoxY = pY + moveY;

	if(hitWall(newBoxX, newBoxY) or hitBox(newBoxX, newBoxY)) return false;

	levelManager->levelMap[pX][pY] = 'O';
	levelManager->levelMap[newBoxX][newBoxY] = 'B';

	return true;
}

void Game::GameLoop() {
	while(isRunning) {
		HandleEvents();
		Update();
		Draw();
	}
	ShutDown();
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
			case 'O':
			case 'P':
				SDL_RenderCopy(renderer, groundTexture, NULL, &rect);
				break;
			case 'B':
				SDL_RenderCopy(renderer, boxTexture, NULL, &rect); 
				break;
			case 'G':
				SDL_RenderCopy(renderer, groundTexture, NULL, &rect);
				SDL_RenderCopy(renderer, goldTexture, NULL, &rect); 
				break;
			default:
				SDL_RenderCopy(renderer, wallTexture, NULL, &rect);
				break;
			}
		}
	}

	player->Draw(renderer);
	SDL_RenderPresent(renderer);
}

SDL_Texture *Game::LoadTexture(char *path)
{
	SDL_Surface *tempSurface = IMG_Load(path);
	if(tempSurface == NULL)
		printf("Failed to load surface Error: %s\n", IMG_GetError());

	SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if(newTexture == NULL)
		printf("Failed to to convert to texture Error: %s\n", SDL_GetError());

	SDL_FreeSurface(tempSurface);

	return newTexture;
}

void Game::ShutDown() {
	SDL_DestroyTexture(wallTexture);
	SDL_DestroyTexture(groundTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

Game::~Game() {
	ShutDown();
}


void Game::HandleEvents() 
{
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) 
			isRunning = false;
		if(event.type == SDL_KEYDOWN)
			switch (event.key.keysym.sym) {
			case SDLK_RIGHT:
				player->relativeMove(1, 0);
				break;
			case SDLK_LEFT:
				player->relativeMove(-1, 0);
				break;
			case SDLK_DOWN:
				player->relativeMove(0, 1);
				break;
			case SDLK_UP:
				player->relativeMove(0, -1);
			default:
				break;
			}
	}

	const Uint8 *keystates = SDL_GetKeyboardState(NULL);

	if(keystates[SDL_SCANCODE_ESCAPE]) 
		isRunning = false;

}

dev