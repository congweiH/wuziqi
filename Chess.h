#pragma once
#include <graphics.h>
#define BOX_SIZE 30


class Chess {
public:
	void draw();
	bool isEmpty();
	void setColor(COLORREF color);
	void setXY(int x, int y);
	void setStyle(int style);
	void setIsnew(bool isnew);
	bool getIsnew();
	int getX();
	int getY();
	int getValue();
	void setValue(int value);

private:
	int x = 0;              // 棋子的 x 坐标
	int y = 0;              // 棋子的 y 坐标
	int value = -1;         // 值（0:白棋, 1:黑棋，-1:空位）
	int style;              // 选中位置的样式, 用于绘制不同的图案
	bool isnew = false;     // 鼠标悬浮在棋盘有选择框，如果isnew为true，那么会重新绘制选择框
	COLORREF color = WHITE; // 棋盘背景色
};