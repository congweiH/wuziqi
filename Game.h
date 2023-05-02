#pragma once
#include "ChessBoard.h"
#include "Player.h"
#include "WhitePlayer.h"
#include "BlackPlayer.h"

#define WINDOW_HEIGHT 520
#define WINDOW_WIDTH 520



class Game {
public:
	Game();
	void init();
	bool waitPlayerPutChess(Player* player, int& oldi, int& oldj);
	void draw();
	void play();
	bool isOver(int playerId);

public:
	int whoWin = -1;		// 谁赢了（0：白棋，1：黑棋，2：平局）
	int total = 0;			// 一共下了多少个棋子
	Player* player[2];		// 两个玩家
	ChessBoard* chessBoard; // 棋盘
};

