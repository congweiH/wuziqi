#include "BlackPlayer.h"

BlackPlayer::BlackPlayer(const string& name) : Player(name, Color::Black) {}

// 下棋
void BlackPlayer::placeChess(ChessBoard* chessBoard, int x, int y) {
	chessBoard->chess[x][y].setValue(1);
	chessBoard->chess[x][y].setIsnew(true);
}