#include "Entity.h"
#include <SDL2/SDL_render.h>

void Entity::relativeMove(int x, int y)
{
	pos.x += x;
	pos.y += y;

	posRect.x = pos.x * TILE_SIZE;
	posRect.y = pos.y * TILE_SIZE;
	printf("%d %d\n", x, y);
}

void Entity::Draw(SDL_Renderer *renderer) 
{
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}

void Entity::move(int x, int y) { 
	pos.x = x; 
	pos.y = y; 

	posRect.x = pos.x * TILE_SIZE;
	posRect.y = pos.y * TILE_SIZE;
}

Vec2 Entity::getPos() {
	return pos;
}
