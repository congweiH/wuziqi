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
	int x = 0;              // ���ӵ� x ����
	int y = 0;              // ���ӵ� y ����
	int value = -1;         // ֵ��0:����, 1:���壬-1:��λ��
	int style;              // ѡ��λ�õ���ʽ, ���ڻ��Ʋ�ͬ��ͼ��
	bool isnew = false;     // ���������������ѡ������isnewΪtrue����ô�����»���ѡ���
	COLORREF color = WHITE; // ���̱���ɫ
};