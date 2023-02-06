#pragma once

#include "EntityWithCollision.h"

class Box : public EntityWithCollision {
public:
	Box(class Game *game) : EntityWithCollision(game, (char*)"assets/box.png") {}
private:
};
