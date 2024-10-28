#include "PlayScene.h"
#include "GameManager.h"

PlayScene::PlayScene() {
    chessBoard = new ChessBoard();
}

PlayScene::~PlayScene() {
    delete chessBoard;
}

void PlayScene::update() {
    if (winner != 0) {
        std::wstring winnerStr = winner == 1 ? L"白棋赢了" : L"黑棋赢了";
        std::wstring content = winnerStr + L"！请问是否继续游戏？";

        int result = MessageBoxW(GetHWnd(), content.c_str() , L"游戏结束", MB_OKCANCEL);

        if (result == IDOK) {
            // 用户点击了确定按钮
            restart();
        } else if (result == IDCANCEL) {
            // 用户点击了取消按钮
            GameManager::getInstance()->running = false;
        }
    }

    winner = chessBoard->hasWinner();
}

void PlayScene::draw() {
    chessBoard->draw();
}

void PlayScene::enter() {
    std::cout << "Enter PlayScene" << std::endl;
    restart();
}

void PlayScene::exit() {
    std::cout << "Exit PlayScene" << std::endl;
}

void PlayScene::handleEvent(const ExMessage &msg) {
    chessBoard->pollEvents(msg);
    if (msg.message == WM_KEYDOWN) {
        int boxResult;
        switch (msg.vkcode) {
            case 'R':
                boxResult = MessageBoxW(GetHWnd(), L"是否重新开始游戏？" , L"提示", MB_OKCANCEL);
                if (boxResult == IDOK) {
                    restart();
                }
                break;
        }
    }
}

void PlayScene::restart() {
    chessBoard->reset();
    winner = 0;
}
