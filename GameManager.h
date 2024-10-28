#pragma once

#include "ChessBoard.h"
#include <string>

#define WINDOW_HEIGHT 440
#define WINDOW_WIDTH 440

#define FPS 144
#define FRAME_TIME (1000 / FPS)

class GameManager {
public:
    GameManager();
    ~GameManager();
    void draw();
    void update();
    void pollEvents();

    void run();

    // 禁止拷贝和赋值操作
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    static GameManager* getInstance();

public:

    static GameManager* instance; // 静态实例指针

    bool running = true;  // 游戏是否正在进行
};