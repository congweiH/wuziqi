#include "Game.h"
#include <iostream>

Game::Game() {
	chessBoard = new ChessBoard();

    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, EX_NOMINIMIZE);	// 初始化窗口，NOMINIMIZE表示不允许最小化
    setbkcolor(WHITE);					// 设置背景颜色
    setbkmode(TRANSPARENT);				// 设置透明文字输出背景

    chessBoard->reset();
}

void Game::draw() {
	cleardevice();
    BeginBatchDraw();
	chessBoard->draw();
    EndBatchDraw();
}

void Game::update() {
    pollEvents();

    int winner = chessBoard->hasWinner();
    if (winner != 0) {
        std::cout << "winner is " << winner << std::endl;
        running = false;
    }
}

void Game::pollEvents() {
    ExMessage msg{};
    if (peekmessage(&msg, EX_KEY | EX_MOUSE)) { // 检查鼠标和键盘消息
        chessBoard->handleExMessage(msg);
        if (msg.message == WM_KEYDOWN) {
            // 处理键盘按键事件
            if (msg.vkcode == VK_ESCAPE) {
                running = false; // 按 ESC 键退出游戏
            }
        }
    }
}