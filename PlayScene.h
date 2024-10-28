#pragma once

#include <iostream>

#include "Scene.h"
#include "ChessBoard.h"

class PlayScene: public Scene {
public:
    PlayScene();
    ~PlayScene();

    void update() override;
    void draw() override;
    void enter() override;
    void exit() override;
    void handleEvent(const ExMessage& msg) override;

    void restart();

    ChessBoard* chessBoard; // 棋盘
    int winner;
};


