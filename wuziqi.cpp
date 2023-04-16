﻿#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <string>
#include <cstring>

using namespace std;

// 整个窗口的大小
const int WINDOW_HEIGHT = 520;
const int WINDOW_WIDTH = 520;

// 格子的长宽
const int BOX_SIZE = 30;
// 地图大小，每一行或者每一列可以下13个棋子
const int MAP_SIZE = 13;
// 坐标（数值）
TCHAR strnum[MAP_SIZE][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") };
// 坐标（字母）
TCHAR strabc[MAP_SIZE][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") };


int dx[4]{ 1, 0, 1, 1 }; // - | \ / 四个方向
int dy[4]{ 0, 1, 1, -1 };

enum Color {
	White,	// 0
	Black	// 1
};

// --------------------------------- Chess ---------------------------
class Chess {
public:
	void draw() {
		COLORREF thefillcolor = getfillcolor(); // 备份填充颜色
		setlinestyle(PS_SOLID, 2);              // 线样式设置
		setfillcolor(color);                    // 填充颜色设置
		solidrectangle(x, y, x + BOX_SIZE, y + BOX_SIZE);   // 绘制无边框的正方形
		if (isnew) {
			// 如果是新下的
			// 绘制边框线
			setlinecolor(LIGHTGRAY);
			line(x + 1, y + 2, x + 8, y + 2);
			line(x + 2, y + 1, x + 2, y + 8);
			line(x + 29, y + 2, x + 22, y + 2);
			line(x + 29, y + 1, x + 29, y + 8);
			line(x + 2, y + 29, x + 8, y + 29);
			line(x + 2, y + 22, x + 2, y + 29);
			line(x + 29, y + 29, x + 22, y + 29);
			line(x + 29, y + 22, x + 29, y + 29);
		}
		setlinecolor(BLACK);
		switch (style) {
			// 以下是不同位置棋盘的样式
		case 0:
			line(x + 15, y, x + 15, y + 30);
			line(x - 1, y + 15, x + 30, y + 15);
			break;
			//  *
			// ***
			//  *
		case 1:
			line(x + 14, y + 15, x + 30, y + 15);
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y, x + 15, y + 30);
			setlinestyle(PS_SOLID, 2);
			break;
			// *
			// ***
			// *
		case 2:
			line(x - 1, y + 15, x + 15, y + 15);
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y, x + 15, y + 30);
			setlinestyle(PS_SOLID, 2);
			break;
			//   *
			// ***
			//   *
		case 3:
			line(x + 15, y + 15, x + 15, y + 30);
			setlinestyle(PS_SOLID, 3);
			line(x - 1, y + 15, x + 30, y + 15);
			setlinestyle(PS_SOLID, 2);
			break;
			// ***
			//  *
			//  *
		case 4:
			line(x + 15, y, x + 15, y + 15);
			setlinestyle(PS_SOLID, 3);
			line(x - 1, y + 15, x + 30, y + 15);
			setlinestyle(PS_SOLID, 2);
			break;
			//  *
			//  *
			// ***
		case 5:
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y, x + 15, y + 15);
			line(x + 15, y + 15, x + 30, y + 15);
			setlinestyle(PS_SOLID, 2);
			break;
			// *
			// *
			// ***
		case 6:
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y, x + 15, y + 15);
			line(x - 1, y + 15, x + 15, y + 15);
			setlinestyle(PS_SOLID, 2);
			break;
			//   *
			//   *
			// ***
		case 7:
			setlinestyle(PS_SOLID, 3);
			line(x - 1, y + 15, x + 15, y + 15);
			line(x + 15, y + 15, x + 15, y + 30);
			setlinestyle(PS_SOLID, 2);
			break;
			// ***
			//   *
			//   *
		case 8:
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y + 15, x + 30, y + 15);
			line(x + 15, y + 15, x + 15, y + 30);
			setlinestyle(PS_SOLID, 2);
			break;
			// ***
			// *
			// *
		case 9:
			line(x + 15, y, x + 15, y + 30);
			line(x - 1, y + 15, x + 30, y + 15);
			setfillcolor(BLACK);
			setlinestyle(PS_SOLID, 1);
			fillcircle(x + 15, y + 15, 4);
			break;
			//  *
			// *O*
			//  *
		}
		switch (value) {
		case 0: // 白棋
			setfillcolor(WHITE);
			setlinestyle(PS_SOLID, 1);
			fillcircle(x + 15, y + 15, 13);
			break;
		case 1: // 黑棋
			setfillcolor(BLACK);
			setlinestyle(PS_SOLID, 1);
			fillcircle(x + 15, y + 15, 13);
			break;
		}
		setfillcolor(thefillcolor); // 还原填充色
	}

	// 位置没有棋子
	bool isEmpty() {
		return this->value == -1;
	}

public:
	int x = 0;              // x 坐标
	int y = 0;              // y 坐标
	int value = -1;         // 值（0:白棋, 1:黑棋，-1:空位）
	int style;               // 选中位置的样式
	bool isnew = false;     // 是否有选择框
	COLORREF color = WHITE; // 棋盘背景色
};
// --------------------------------- Chess  end ---------------------------


// ----------------------- ChessBoard ------------------
// 棋盘
class ChessBoard {
public:
	void show() {
		int style = 0;  // 棋盘样式
		for (int i = 0, k = 0; i < BOX_SIZE * MAP_SIZE; i += BOX_SIZE) {
			for (int j = 0, g = 0; j < BOX_SIZE * MAP_SIZE; j += BOX_SIZE) {
				box[k][g].color = RGB(255, 205, 150);// 棋盘底色
				// x、y 坐标
				box[k][g].x = 65 + j;
				box[k][g].y = 50 + i;
				// 棋盘样式的判断
				if (k == 0 && g == 0) {
					style = 8;
				}
				else if (k == 0 && g == MAP_SIZE - 1) {
					style = 7;
				}
				else if (k == MAP_SIZE - 1 && g == MAP_SIZE - 1) {
					style = 6;
				}
				else if (k == MAP_SIZE - 1 && g == 0) {
					style = 5;
				}
				else if (k == 0) {
					style = 3;
				}
				else if (k == MAP_SIZE - 1) {
					style = 4;
				}
				else if (g == 0) {
					style = 1;
				}
				else if (g == MAP_SIZE - 1) {
					style = 2;
				}
				else  if ((k == 3 && g == 3) || (k == 3 && g == 15) || (k == 15 && g == 3) || (k == 15 && g == 15) || (k == 3 && g == 9) || (k == 9 && g == 3) || (k == 15 && g == 9) || (k == 9 && g == 15) || (k == 9 && g == 9)) {
					style = 9;
				}
				else {
					style = 0;
				}
				box[k][g].style = style;
				box[k][g].draw(); // 绘制
				if (box[k][g].isnew == true) {
					box[k][g].isnew = false; // 把上一个下棋位置的黑框清除
				}
				g++;
			}
			k++;
		}
		// 画坐标
		LOGFONT nowstyle;
		gettextstyle(&nowstyle);
		settextstyle(0, 0, NULL);
		int number = 0; // 坐标输出的位置
		for (int i = 0; i < MAP_SIZE; i++) {
			outtextxy(75 + number, 35, strnum[i]);
			outtextxy(53, 55 + number, strabc[i]);
			number += BOX_SIZE;
		}
		settextstyle(&nowstyle);
	}

	bool canPut(int i, int j, MOUSEMSG mouse) {
		return mouse.x > this->box[i][j].x && mouse.x < this->box[i][j].x + BOX_SIZE//判断x坐标
			&& mouse.y > this->box[i][j].y && mouse.y < this->box[i][j].y + BOX_SIZE//判断y坐标
			&& this->box[i][j].isEmpty();//判断是否是空位置
	}
public:
	Chess box[MAP_SIZE][MAP_SIZE];      // 棋盘
};

// ----------------------- ChessBoard ------------------



// ---------------------- Player ----------------
class Player {
public:
	Player(const string& name, int color) : name(name), color(color) {}

	virtual void placeChess(int x, int y) = 0;
private:
	string name;
	int color;
};

class WhitePlayer : public Player {
public:
	WhitePlayer(const string& name) : Player(name, Color::White) {}

	void placeChess(int x, int y) {

	}
};

class BlackPlayer : public Player {
public:
	BlackPlayer(const string& name) : Player(name, Color::Black) {}

	void placeChess(int x, int y) {

	}
};
// ----------------------- Player end ----------------------- 

// ------------------  Game ----------------------
class Game {
public:
	Game() {
		initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, NOMINIMIZE);	// 初始化窗口，NOMINIMIZE表示不允许最小化
		setbkcolor(WHITE);					// 设置背景颜色
		setbkmode(TRANSPARENT);				// 设置透明文字输出背景


		this->player[0] = new BlackPlayer("张三");
		this->player[1] = new BlackPlayer("李四");
		this->chessBoard = new ChessBoard();
	}
	void init() {
		this->whoWin = -1;// 谁赢了
		this->total = 0;
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				this->chessBoard->box[i][j].value = -1;	// 表示空位置
			}
		}
		cleardevice();
		// 绘制背景
		setfillcolor(RGB(255, 205, 150));
		solidrectangle(40, 25, 475, 460);
		// 设置字体样式
		settextstyle(30, 15, 0, 0, 0, 1000, false, false, false);
		settextcolor(BLACK);
	}

	bool waitPlayerPutChess(Player *player, int &oldi, int &oldj, int playerId) {
		while (1) {
			MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
			for (int i = 0; i < MAP_SIZE; i++) {
				for (int j = 0; j < MAP_SIZE; j++) {
					if (this->chessBoard->canPut(i, j, mouse)) {
						// 如果停在某一个空位置上面
						if (mouse.mkLButton) {
							// 如果按下了
							this->total++;						// 下棋个数+1
							this->chessBoard->box[i][j].value = playerId;	// 下棋
							this->chessBoard->box[i][j].isnew = true;				// 新位置更新
							oldi = -1;
							oldj = -1;
							return true;
						}
						// 更新选择框
						this->chessBoard->box[oldi][oldj].isnew = false;
						this->chessBoard->box[oldi][oldj].draw();
						this->chessBoard->box[i][j].isnew = true;
						this->chessBoard->box[i][j].draw();
						oldi = i;
						oldj = j;
					}
				}
			}
		}
	}

	void play() {
		// 上一个鼠标停的坐标
		int oldi = 0;
		int oldj = 0;
		this->chessBoard->show(); // 绘制
		// 0 白棋先下, 1 黑棋后下, 轮循
		int curPlayerId = 0;
		while (1) {
			// 等待玩家放棋子
			if (this->waitPlayerPutChess(this->player[curPlayerId], oldi, oldj, curPlayerId)) {
				this->chessBoard->show();
				if (this->isOver(curPlayerId)) {
					break;
				}
				curPlayerId = !curPlayerId;  // 0 变 1， 1 变 0 
			}
		}
	}

	bool isOver(int playerId) {
		bool isInit = true; // 是否刚刚开局
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				if (!this->chessBoard->box[i][j].isEmpty()) {
					// 遍历每个可能的位置
					isInit = false;                 // 如果有，那么就不是刚刚开局
					int nowcolor = this->chessBoard->box[i][j].value; // 现在遍历到的颜色
					int length[4] = { 0, 0, 0, 0 };    // 四个方向的长度
					for (int k = 0; k < 4; k++) {
						// 原理同寻找最佳位置
						int nowi = i;
						int nowj = j;
						while (nowi < MAP_SIZE && nowj < MAP_SIZE && nowi >= 0 && nowj >= 0 && this->chessBoard->box[nowi][nowj].value == nowcolor)
						{
							length[k]++;
							nowj += dx[k];
							nowi += dy[k];
						}
						nowi = i;
						nowj = j;
						while (nowi < MAP_SIZE && nowj < MAP_SIZE && nowi >= 0 && nowj >= 0 && this->chessBoard->box[nowi][nowj].value == 1 - nowcolor) {
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
		// 胜利处理
		settextcolor(RGB(0, 255, 0));
		Sleep(1000);
		if (this->whoWin == 0) {
			outtextxy(260, 260, _T("白胜"));
		}
		else if (this->whoWin == 1) {
			outtextxy(260, 260, _T("黑胜"));
		}
		else if (this->whoWin == 2) {
			outtextxy(260, 260, _T("平局"));
		}
		// 给反应时间
		Sleep(5000);
		return true;
	}

public:
	int whoWin = -1;		// 谁赢了（0：白棋，1：黑棋，2：平局）
	int total = 0;			// 一共下了多少个棋子
	Player* player[2];
	ChessBoard* chessBoard;
};
// --------------- Game end ----------------------


// main函数
int main() {
	Game* game = new Game();
	
	while (1) {
		game->init(); // 初始化
		game->play(); // 游戏开始
	}
}