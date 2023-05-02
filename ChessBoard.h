#pragma once

#include "Chess.h"
#define MAP_SIZE 13

class ChessBoard {
public:
	void draw();
	bool canPut(int i, int j, ExMessage mouse);

public:
	Chess chess[MAP_SIZE][MAP_SIZE];      // 棋盘
};

