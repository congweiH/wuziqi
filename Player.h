#pragma once
#include <string>
#include "ChessBoard.h"
using namespace std;

enum Color {
	White,	// 0
	Black	// 1
};

class Player {
public:
	Player(const string& name, int color);
	virtual void placeChess(ChessBoard* chessBoard, int x, int y) = 0;

private:
	string name;	// 玩家名称
	int color;		// 玩家的颜色
};