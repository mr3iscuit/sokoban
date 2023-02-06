#pragma once

#include "Game.h"
#include <SDL2/SDL_render.h>

struct Vec2 {
	int x;
	int y;
};

class Entity {
public:
	Entity(class Game *game) {
		this->game = game;
	}

private:
	Vec2 pos;
	SDL_Texture *texture;
	SDL_Rect posRect, spriteRect;
	class Game* game;
};

