#pragma once

#include "EntityWithCollision.h"

class Player : public EntityWithCollision {
public:
	Player(class Game *game) : EntityWithCollision(game, (char*)"assets/player.png") {}
private:
};
