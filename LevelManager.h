#pragma once

#include <string>

#include "Utils.h"
#include "fstream"

class LevelManager {
public:
	void LoadLevel(char *file);
	char getChar(int r, int c) { return levelMap[r][c]; }
	char levelMap[TILE_ROWS][TILE_COLS] = { '0' };

private:
	std::ifstream levelFile;
};
