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
	int whoWin = -1;		// ˭Ӯ�ˣ�0�����壬1�����壬2��ƽ�֣�
	int total = 0;			// һ�����˶��ٸ�����
	Player* player[2];		// �������
	ChessBoard* chessBoard; // ����
};

