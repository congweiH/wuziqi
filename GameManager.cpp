#include "GameManager.h"
#include "SceneManager.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {
}

GameManager::~GameManager() {
    delete SceneManager::getInstance();
}

void GameManager::update() {
    SceneManager::getInstance()->update();
}

void GameManager::pollEvents() {
    ExMessage msg{};
    if (peekmessage(&msg, EX_KEY | EX_MOUSE)) { // 检查鼠标和键盘消息
        SceneManager::getInstance()->handleMessage(msg);
        if (msg.message == WM_KEYDOWN) {
            int boxResult;
            switch (msg.vkcode) {
                case VK_ESCAPE:
                    boxResult = MessageBoxW(GetHWnd(), L"是否退出游戏？", L"提示", MB_OKCANCEL);
                    if (boxResult == IDOK) {
                        GameManager::getInstance()->running = false;
                    }
                    break;
            }
        }
    }
}

void GameManager::draw() {
    SceneManager::getInstance()->draw();
}

void GameManager::run() {
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

GameManager *GameManager::getInstance() {
    if (!instance) {
        instance = new GameManager();
    }
    return instance;
}
