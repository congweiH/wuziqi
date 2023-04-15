#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>

// 格子的长宽
const int BOX_SIZE = 30;
const int BOX_NUMBER = 19;   // 19根线，也就是18个格子

// 类定义

// 保存位置的类
class Seat {
  public:
	int i = 0;      // y 坐标
	int j = 0;      // x 坐标
	int number = 0; // 分数
};

// 保存棋盘的类
class Box {
public:
	void draw();	        // 绘制棋盘

 public:
	int x = 0;              // x 坐标
	int y = 0;              // y 坐标
	int value = -1;         // 值（黑棋：1，白棋：0，空位：-1）
	int modle;              // 模式
	bool isnew = false;     // 是否有选择框
	int number = 0;         // 分数
	COLORREF color = WHITE; // 棋盘背景色
};


// 函数声明
void draw();                  // 绘制
void init();                  // 初始化
Seat findBestSeat(int color); // 寻找最佳位置
void isWIN();                 // 判断输赢
void game();                  // 游戏主函数



// main函数
int main() {
	initgraph(700, 700, NOMINIMIZE); // 初始化绘图环境
	setbkcolor(WHITE);
	cleardevice();
	setbkmode(TRANSPARENT); // 设置透明文字输出背景
	while (1) {
		init(); // 初始化
		game(); // 游戏开始
		cleardevice();
	}
}



// 全局变量
Box box[19][19];      // 棋盘
int win = -1;         // 谁赢了（0：白棋，1：黑棋，2：平局）
int whoplay = 0;      // 轮到谁下棋了
int playercolor = 0;  // 玩家颜色
int dx[4]{ 1,0,1,1 }; // - | \ / 四个方向
int dy[4]{ 0,1,1,-1 };



// 类函数定义

// 绘制函数
void Box::draw() {
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
	switch (modle) {
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
	switch (value)
	{
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



// 其他函数定义

// 绘制棋盘
void draw() {
	int modle = 0;  // 棋盘样式
	int number = 0; // 坐标输出的位置
	// 坐标（数值）
	TCHAR strnum[19][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15") ,_T("16") ,_T("17"),_T("18"),_T("19") };
	// 坐标（字母）
	TCHAR strabc[19][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") ,_T("N"),_T("O") ,_T("P") ,_T("Q"),_T("R"),_T("S") };
	for (int i = 0, k = 0; i < 570; i += 30)
	{
		for (int j = 0, g = 0; j < 570; j += 30)
		{
			box[k][g].color = RGB(255, 205, 150);// 棋盘底色
			// x、y 坐标
			box[k][g].x = 65 + j;
			box[k][g].y = 50 + i;
			box[k][g].number = 0;// 初始化分数
			// 棋盘样式的判断
			if (k == 0 && g == 0)
			{
				modle = 8;
			}
			else if (k == 0 && g == 18)
			{
				modle = 7;
			}
			else if (k == 18 && g == 18)
			{
				modle = 6;
			}
			else if (k == 18 && g == 0)
			{
				modle = 5;
			}
			else if (k == 0)
			{
				modle = 3;
			}
			else if (k == 18)
			{
				modle = 4;
			}
			else if (g == 0)
			{
				modle = 1;
			}
			else if (g == 18)
			{
				modle = 2;
			}
			else  if ((k == 3 && g == 3) || (k == 3 && g == 15) || (k == 15 && g == 3) || (k == 15 && g == 15) || (k == 3 && g == 9) || (k == 9 && g == 3) || (k == 15 && g == 9) || (k == 9 && g == 15) || (k == 9 && g == 9))
			{
				modle = 9;
			}
			else
			{
				modle = 0;
			}
			box[k][g].modle = modle;
			box[k][g].draw(); // 绘制
			if (box[k][g].isnew == true)
			{
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
	for (int i = 0; i < 19; i++)
	{
		outtextxy(75 + number, 35, strnum[i]);
		outtextxy(53, 55 + number, strabc[i]);
		number += 30;
	}
	settextstyle(&nowstyle);
}

// 对局初始化
void init() {
	win = -1;// 谁赢了
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			box[i][j].number = 0;// 分数
			box[i][j].value = -1;// 值
		}
	}
}



// 核心函数

// 寻找最佳位置
Seat findBestSeat(int color)
{
	// 评分表
	int Score[3][5] = {
		{ 0, 20, 360, 5800, 92840 }, // 防守0子
		{ 0, 0, 20, 360, 92840 },    // 防守1子
		{ 0, 0, 0, 0, 92840 }        // 防守2子
	};
	Seat bestseat;              // 最佳位置
	int MAXnumber[361] = { 0 }; // 最佳分数（可能有多个）
	int MAXx[361] = { 0 };      // 最佳 x 坐标（可能有多个）
	int MAXy[361] = { 0 };      // 最佳 y 坐标（可能有多个）
	int number = 0;             // 下一个最佳分数储存位置
	int truenumber;             // 输出的最佳分数位置
	int nowi = 0;               // 现在遍历到的y坐标
	int nowj = 0;               // 现在遍历到的x坐标
	int length[4];              // 四个方向的长度
	int emeny[4];               // 四个方向的敌子
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (box[i][j].value == -1)
			{
				// 遍历每一个可能的位置

				// 自己
				box[i][j].value = color; // 尝试下在这里
				for (int k = 0; k < 4; k++)
				{
					length[k] = 0;
					emeny[k] = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && box[nowi][nowj].value == color)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					if (box[nowi][nowj].value == 1 - color || nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18)
					{
						emeny[k]++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && box[nowi][nowj].value == color)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
					if (box[nowi][nowj].value == 1 - color || nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18)
					{
						emeny[k]++;
					}
					length[k] -= 2; // 判断长度
					if (length[k] > 4)
					{
						length[k] = 4;
					}
					box[i][j].number += Score[emeny[k]][length[k]] * 4 + !(!length[k]) * 20;//加分系统
					length[k] = 0;
					emeny[k] = 0;
				}
				// 敌人（原理同上）
				box[i][j].value = 1 - color;
				for (int k = 0; k < 4; k++)
				{
					length[k] = 0;
					emeny[k] = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && box[nowi][nowj].value == 1 - color)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					if (box[nowi][nowj].value == color || nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18)
					{
						emeny[k]++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && box[nowi][nowj].value == 1 - color)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
					if (box[nowi][nowj].value == color || nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18)
					{
						emeny[k]++;
					}
					length[k] -= 2;
					if (length[k] > 4)
					{
						length[k] = 4;
					}
					box[i][j].number += Score[emeny[k]][length[k]];
					length[k] = 0;
					emeny[k] = 0;
				}
				box[i][j].value = -1;
			}
			if (box[i][j].number == MAXnumber[0])
			{
				// 如果和最高分数相同
				MAXnumber[number] = box[i][j].number;
				MAXy[number] = i;
				MAXx[number] = j;
				number++;
				// 新增一个分数及坐标
			}
			if (box[i][j].number > MAXnumber[0])
			{
				// 如果比最高分数高
				for (int k = 0; k < number; k++)
				{
					MAXnumber[k] = 0;
					MAXy[k] = 0;
					MAXx[k] = 0;
				}
				number = 0;
				MAXnumber[number] = box[i][j].number;
				MAXy[number] = i;
				MAXx[number] = j;
				number++;
				// 清空数组再加入
			}
		}
	}
	// 生成随机位置
	srand(time(NULL));
	truenumber = rand() % number;
	bestseat.i = MAXy[truenumber];
	bestseat.j = MAXx[truenumber];
	bestseat.number = MAXnumber[truenumber];
	// 返回位置
	return bestseat;
}

// 判断输赢
void isWIN()
{
	bool isinit = true; // 是否刚刚开局
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (box[i][j].value != -1)
			{
				// 遍历每个可能的位置
				isinit = false;                 // 如果有，那么就不是刚刚开局
				int nowcolor = box[i][j].value; // 现在遍历到的颜色
				int length[4] = { 0,0,0,0 };    // 四个方向的长度
				for (int k = 0; k < 4; k++)
				{
					// 原理同寻找最佳位置
					int nowi = i;
					int nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && box[nowi][nowj].value == nowcolor)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && box[nowi][nowj].value == 1 - nowcolor)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
				}
				for (int k = 0; k < 4; k++)
				{
					if (length[k] >= 5) {
						// 如果满五子
						if (nowcolor == playercolor)
						{
							win = playercolor; // 玩家胜
						}
						if (nowcolor == 1 - playercolor)
						{
							win = 1 - playercolor; // 电脑胜
						}
					}
				}
				if ((!isinit) && findBestSeat(playercolor).number == 0 && findBestSeat(1 - playercolor).number == 0)
				{
					// 如果不是开局且双方无最佳位置
					win = 2; // 平局
				}
			}
		}
	}
}

// 游戏主函数
void game()
{
	// 上一个鼠标停的坐标
	int oldi = 0;
	int oldj = 0;
	// 随机化玩家颜色
	srand(time(NULL));
	playercolor = rand() % 2;
	// 绘制背景
	setfillcolor(RGB(255, 205, 150));
	solidrectangle(40, 25, 645, 630);
	// 设置字体样式
	settextstyle(30, 15, 0, 0, 0, 1000, false, false, false);
	settextcolor(BLACK);
	// 输出标示语
	if (playercolor == 0)
	{
		outtextxy(150, 650, _T("玩家执白后行，电脑执黑先行"));
		whoplay = 1;
	}
	else
	{
		outtextxy(150, 650, _T("玩家执黑先行，电脑执白后行"));
		whoplay = 0;
	}
	draw(); // 绘制
	while (1)
	{
	NEXTPLAYER:
		if (whoplay == 0)
		{
			// 玩家下棋
			MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息
			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 19; j++)
				{
					if (mouse.x > box[i][j].x && mouse.x<box[i][j].x + 30//判断x坐标
						&& mouse.y>box[i][j].y && mouse.y < box[i][j].y + 30//判断y坐标
						&& box[i][j].value == -1)//判断是否是空位置
					{
						// 如果停在某一个空位置上面
						if (mouse.mkLButton)
						{
							// 如果按下了
							box[i][j].value = playercolor; // 下棋
							box[i][j].isnew = true;        // 新位置更新
							oldi = -1;
							oldj = -1;
							// 下一个玩家
							whoplay = 1;
							goto DRAW;
						}
						// 更新选择框
						box[oldi][oldj].isnew = false;
						box[oldi][oldj].draw();
						box[i][j].isnew = true;
						box[i][j].draw();
						oldi = i;
						oldj = j;
					}
				}
			}
		}
		else
		{
			// 电脑下棋
			Seat best;
			best = findBestSeat(1 - playercolor); // 寻找最佳位置
			if (best.number == 0)
			{
				// 开局情况
				int drawi = 9;
				int drawj = 9;
				while (box[drawi][drawj].value != -1)
				{
					drawi--;
					drawj++;
				}
				box[drawi][drawj].value = 1 - playercolor;
				box[drawi][drawj].isnew = true;
			}
			else
			{
				box[best.i][best.j].value = 1 - playercolor;//下在最佳位置
				box[best.i][best.j].isnew = true;
			}
			whoplay = 0;
			goto DRAW; // 轮到下一个
		}
	}
DRAW: // 绘制
	isWIN(); // 检测输赢
	draw();
	if (win == -1)
	{
		// 如果没有人胜利
		Sleep(500);
		goto NEXTPLAYER; // 前往下一个玩家
	}
	// 胜利处理
	settextcolor(RGB(0, 255, 0));
	Sleep(1000);
	if (win == 0)
	{
		outtextxy(320, 320, _T("白胜"));
	}
	if (win == 1)
	{
		outtextxy(320, 320, _T("黑胜"));
	}
	if (win == 2)
	{
		outtextxy(320, 320, _T("平局"));
	}
	// 给反应时间
	Sleep(5000);
	return;
}