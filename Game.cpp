#include "Game.h"

int dx[4]{ 1, 0, 1, 1 }; // - | \ / 四个方向
int dy[4]{ 0, 1, 1, -1 };

TCHAR message[3][20] = { _T("白胜"), _T("黑胜"), _T("平局")};

Game::Game() {
	this->player[0] = new WhitePlayer("白棋");
	this->player[1] = new BlackPlayer("黑棋");
	this->chessBoard = new ChessBoard();
}

// 游戏初始化
void Game::init() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, NOMINIMIZE);	// 初始化窗口，NOMINIMIZE表示不允许最小化
	setbkcolor(WHITE);					// 设置背景颜色
	setbkmode(TRANSPARENT);				// 设置透明文字输出背景
}

// 等待玩家下棋
bool Game::waitPlayerPutChess(Player* player, int& oldi, int& oldj) {
	while (1) {
		MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				if (this->chessBoard->canPut(i, j, mouse)) {
					// 如果停在某一个空位置上面
					if (mouse.mkLButton) {
						// 如果按下了
						this->total++;						// 下棋个数+1
						player->placeChess(chessBoard, i, j);
						oldi = -1;
						oldj = -1;
						return true;
					}
					// 更新选择框
					this->chessBoard->chess[oldi][oldj].setIsnew(false);
					this->chessBoard->chess[oldi][oldj].draw();
					this->chessBoard->chess[i][j].setIsnew(true);
					this->chessBoard->chess[i][j].draw();
					oldi = i;
					oldj = j;
				}
			}
		}
	}
}

void Game::draw() {
	this->whoWin = -1;// 谁赢了
	this->total = 0;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			this->chessBoard->chess[i][j].setValue(-1);	// 表示空位置
		}
	}
	cleardevice();
	// 绘制背景
	setfillcolor(RGB(255, 205, 150));
	solidrectangle(40, 25, 475, 460);
	// 设置字体样式
	settextstyle(30, 15, 0, 0, 0, 1000, false, false, false);
	settextcolor(BLACK);
	this->chessBoard->show(); // 绘制
}

// 开始游戏
void Game::play() {
	// 上一个鼠标停的坐标
	int oldi = 0;
	int oldj = 0;
	// 0 白棋先下, 1 黑棋后下, 轮循
	int curPlayerId = 0;
	while (1) {
		// 等待玩家放棋子
		if (this->waitPlayerPutChess(this->player[curPlayerId], oldi, oldj)) {
			this->chessBoard->show();
			if (this->isOver(curPlayerId)) {
				// 弹框提示
				MessageBox(GetHWnd(), message[this->whoWin], _T("游戏结束"), MB_ICONWARNING);
				break;
			}
			curPlayerId = !curPlayerId;  // 0 变 1， 1 变 0 
		}
	}
}

// 判断游戏是否结束
bool Game::isOver(int playerId) {
	bool isInit = true; // 是否刚刚开局
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (!this->chessBoard->chess[i][j].isEmpty()) {
				// 遍历每个可能的位置
				isInit = false;                 // 如果有，那么就不是刚刚开局
				int nowcolor = this->chessBoard->chess[i][j].getValue(); // 现在遍历到的颜色
				int length[4] = { 0, 0, 0, 0 };    // 四个方向的长度
				for (int k = 0; k < 4; k++) {
					// 原理同寻找最佳位置
					int nowi = i;
					int nowj = j;
					while (nowi < MAP_SIZE && nowj < MAP_SIZE && nowi >= 0 && nowj >= 0 && this->chessBoard->chess[nowi][nowj].getValue() == nowcolor)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					nowi = i;
					nowj = j;
					while (nowi < MAP_SIZE && nowj < MAP_SIZE && nowi >= 0 && nowj >= 0 && this->chessBoard->chess[nowi][nowj].getValue() == 1 - nowcolor) {
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
				}
				for (int k = 0; k < 4; k++) {
					// 如果满五子
					if (length[k] >= 5) {
						this->whoWin = playerId;
					}
				}
				// 全都下满了都没有位置了
				if (this->total == MAP_SIZE * MAP_SIZE) {
					this->whoWin = 2; // 平局
				}
			}
		}
	}
	if (this->whoWin == -1) {
		// 如果没有人胜利
		Sleep(500);
		return false;
	}
	return true;
}