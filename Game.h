#pragma once

#include "ChessBoard.h"

#define WINDOW_HEIGHT 520
#define WINDOW_WIDTH 520

class Game {
public:
    Game();
    void draw();
    void update();
    void pollEvents();

public:
    ChessBoard* chessBoard; // 棋盘
    bool running = true;  // 游戏是否正在进行
};