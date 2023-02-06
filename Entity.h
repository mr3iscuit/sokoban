#pragma once

#include "Game.h"
#include "Utils.h"
#include <SDL2/SDL_render.h>

struct Vec2 {
	int x;
	int y;
};

class Entity {
public:
	Entity(class Game *game, char *texturePath) {
		this->game = game;
		texture = game->LoadTexture(texturePath);
		pos = { 0, 0 };
		posRect = { pos.x, pos.y, TILE_SIZE, TILE_SIZE };
		spriteRect = { 0, 0, TILE_SIZE, TILE_SIZE };
	}

	void Draw(SDL_Renderer *renderer);
	void relativeMove(int x, int y);
	void move(int x, int y); 
	Vec2 getPos();

protected:
	Vec2 pos;
	SDL_Texture *texture;
	SDL_Rect posRect, spriteRect;
	class Game* game;
};

