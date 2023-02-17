#define SDL_MAIN_HANDLED

#include "Game.h"

int main(int argc, char **argv) 
{
	Game g;
	g.GameLoop();
	return 0;
}
