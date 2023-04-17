#pragma once
#include "Player.h"

class BlackPlayer: public Player {
public:
	BlackPlayer(const string& name);
	void placeChess(ChessBoard* chessBoard, int x, int y);
};
