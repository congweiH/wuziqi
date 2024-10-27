#include "Game.h"

Game::Game() {
    chessBoard = new ChessBoard();

    restart();
}

void Game::draw() {
    chessBoard->draw();
}

void Game::update() {
    if (winner != 0) {
        std::wstring winnerStr = winner == 1 ? L"白棋赢了" : L"黑棋赢了";
        std::wstring content = winnerStr + L"！请问是否继续游戏？";

        int result = MessageBoxW(GetHWnd(), content.c_str() , L"游戏结束", MB_OKCANCEL);

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
            int boxResult;
            switch (msg.vkcode) {
                case VK_ESCAPE:
                    boxResult = MessageBoxW(GetHWnd(), L"是否退出游戏？", L"提示", MB_OKCANCEL);
                    if (boxResult == IDOK) {
                        running = false;
                    }
                    break;
                case 'R':
                    boxResult = MessageBoxW(GetHWnd(), L"是否重新开始游戏？" , L"提示", MB_OKCANCEL);
                    if (boxResult == IDOK) {
                        restart();
                    }
                    break;
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

    BeginBatchDraw();
    while (running) {
        DWORD start = GetTickCount();

        pollEvents();
        update();

        cleardevice();
        draw();
        FlushBatchDraw();

        DWORD elapsed = GetTickCount() - start;
        if (elapsed < FRAME_TIME) {
            Sleep(FRAME_TIME - elapsed);
        }
    }
    EndBatchDraw();
    closegraph();
}
