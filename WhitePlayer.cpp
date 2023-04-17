#include "WhitePlayer.h"


WhitePlayer::WhitePlayer(const string& name) : Player(name, Color::White) {}

// ÏÂÆå
void WhitePlayer::placeChess(ChessBoard* chessBoard, int x, int y) {
	chessBoard->chess[x][y].setValue(0);
	chessBoard->chess[x][y].setIsnew(true);
}