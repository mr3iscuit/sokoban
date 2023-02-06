#include <stdio.h>

#include "LevelManager.h"
#include "Utils.h"
#include "fstream"

void LevelManager::LoadLevel(char *file)
{
	int rowCount = 0;
	int colCount = 0;

	levelFile.open(file);
	if(levelFile.is_open()) {
		char inChar;
		while (levelFile.get(inChar)) {
			//TODO fix load logic.
			if (inChar == '\n') {
				colCount = 0;
				rowCount++;
			}
			else if(inChar <= 'Z' and inChar >= 'A'){
				levelMap[colCount][rowCount] = inChar;
				colCount++;
			}
		}
	}

	levelFile.close();

	for(int r = 0; r < TILE_ROWS; r++) {
		for (int c = 0; c < TILE_COLS; c++) {
			printf("%c", levelMap[c][r]);
		}
		printf("\n");
	}
	printf("%d %d\n", TILE_ROWS, TILE_COLS);
}

