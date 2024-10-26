#pragma once

#include "ChessBoard.h"
#include <string>

#define WINDOW_HEIGHT 440
#define WINDOW_WIDTH 440

class Game {
public:
    Game();
    ~Game();
    void draw();
    void update();
    void pollEvents();
    void restart();

public:
    ChessBoard* chessBoard; // 棋盘
    bool running = true;  // 游戏是否正在进行
    int winner;
    HWND windowHandle;
};