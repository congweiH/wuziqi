#include "Game.h"
#include "Utils.h"

Game::Game() {
    chessBoard = new ChessBoard();

    restart();
}

void Game::draw() {
    chessBoard->draw();
}

void Game::update() {
    if (winner != 0) {
        std::string winnerStr = winner == 1 ? "白棋赢了" : "黑棋赢了";
        std::string content = std::string(winnerStr + "！" + "请问是否继续游戏？");

        wchar_t* wideString = Utils::stringToWideChar(content);
        int result = MessageBoxW(GetHWnd(), wideString , L"游戏结束", MB_OKCANCEL);
        // 释放内存
        delete[] wideString;

        if (result == IDOK) {
            // 用户点击了确定按钮
            restart();
        } else if (result == IDCANCEL) {
            // 用户点击了取消按钮
            running = false;
        }
    }

    winner = chessBoard->hasWinner();
}

void Game::pollEvents() {
    ExMessage msg{};
    if (peekmessage(&msg, EX_KEY | EX_MOUSE)) { // 检查鼠标和键盘消息
        chessBoard->pollEvents(msg);
        if (msg.message == WM_KEYDOWN) {
            // 处理键盘按键事件
            if (msg.vkcode == VK_ESCAPE) {
                running = false; // 按 ESC 键退出游戏
            }
        }
    }
}

void Game::restart() {
    chessBoard->reset();
    winner = 0;
}

Game::~Game() {
    delete chessBoard;
}

void Game::run() {
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, EX_NOMINIMIZE);	// 初始化窗口，NOMINIMIZE表示不允许最小化
    setbkcolor(WHITE);					// 设置背景颜色
    setbkmode(TRANSPARENT);				// 设置透明文字输出背景

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    BeginBatchDraw();
    while (running) {
        QueryPerformanceCounter(&start);

        pollEvents();
        update();

        cleardevice();
        draw();
        FlushBatchDraw();

        QueryPerformanceCounter(&end);
        double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        if (elapsed < FPS_INTERVAL) {
            Sleep((long)((FPS_INTERVAL - elapsed) * 1000));
        }
    }
    EndBatchDraw();
    closegraph();
}
