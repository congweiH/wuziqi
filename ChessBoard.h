#pragma once

#include <easyx.h>

#define BOX_WIDTH 30
#define BOX_COUNT 12

class ChessBoard {
public:
	void draw();
    void reset();
    void putWhiteChess(int i, int j);
    void putBlackChess(int i, int j);
    void handleExMessage(const ExMessage& msg);
    bool pixelToChess(int x, int y, int& i, int& j) const;  // 像素坐标转化为棋盘坐标, 返还是否在棋盘内
    int hasWinner();                  // 是否有胜利者

public:
	int chess[BOX_COUNT + 1][BOX_COUNT + 1];      // 值（1:白棋, -1:黑棋，0:空位）
    int player;                        // 1是白色，-1是黑色
    int offsetX, offsetY;                    // 棋盘左上角坐标
    void putChess(int i, int j);
    int aimX, aimY;                          // 鼠标目标坐标
};