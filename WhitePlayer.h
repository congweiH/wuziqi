#pragma once
#include "Player.h"

class WhitePlayer: public Player {
public:
	WhitePlayer(const string& name);
	void placeChess(ChessBoard* chessBoard, int x, int y);
};