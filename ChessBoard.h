#pragma once

#include "Chess.h"
#define MAP_SIZE 13

class ChessBoard {
public:
	void show();
	bool canPut(int i, int j, MOUSEMSG mouse);

public:
	Chess chess[MAP_SIZE][MAP_SIZE];      // ∆Â≈Ã
};

