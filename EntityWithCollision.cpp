#include "EntityWithCollision.h"

bool EntityWithCollision::relativeMove(int x, int y)
{
	int newx = pos.x + x, newy = pos.y + y;
	if(game->hitWall(newx, newy)) return false;
	if(game->hitBox(newx, newy)) 
		if(!game->moveBox(x, y)) return false;
	move(newx, newy);
	return true;
}
