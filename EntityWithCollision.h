#pragma once

#include "Entity.h"

class EntityWithCollision : public Entity {
public:
	EntityWithCollision(class Game *game, char *texturePath) : Entity(game, texturePath) {}
	bool relativeMove(int x, int y);
private:
};
