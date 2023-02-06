#pragma once

#include "Entity.h"

class Player : public Entity {
public:
	Player(class Game *game) : Entity(game, (char*)"assets/player.png") {}
private:
};
