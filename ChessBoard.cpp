#include "ChessBoard.h"

// ������
void ChessBoard::show() {
	int style = 0;  // ������ʽ
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			this->chess[i][j].setColor(RGB(255, 205, 150));	// ���̵�ɫ
			// x��y ����
			this->chess[i][j].setXY(65 + j * BOX_SIZE, 50 + i * BOX_SIZE);
			// ������ʽ���ж�
			if (i == 0 && j == 0) {
				style = 8;
			}
			else if (i == 0 && j == MAP_SIZE - 1) {
				style = 7;
			}
			else if (i == MAP_SIZE - 1 && j == MAP_SIZE - 1) {
				style = 6;
			}
			else if (i == MAP_SIZE - 1 && j == 0) {
				style = 5;
			}
			else if (i == 0) {
				style = 3;
			}
			else if (i == MAP_SIZE - 1) {
				style = 4;
			}
			else if (j == 0) {
				style = 1;
			}
			else if (j == MAP_SIZE - 1) {
				style = 2;
			}
			else  if ((i == 3 && j == 3) || (i == 3 && j == 15) || (i == 15 && j == 3) || (i == 15 && j == 15) || (i == 3 && j == 9) || (i == 9 && j == 3) || (i == 15 && j == 9) || (i == 9 && j == 15) || (i == 9 && j == 9)) {
				style = 9;
			}
			else {
				style = 0;
			}
			this->chess[i][j].setStyle(style);
			this->chess[i][j].draw(); // ����
			if (chess[i][j].getIsnew() == true) {
				chess[i][j].setIsnew(false); // ����һ������λ�õĺڿ����
			}
		}
	}
	// ������
	LOGFONT nowstyle;
	gettextstyle(&nowstyle);
	settextstyle(0, 0, NULL);

	int number = 0; // ���������λ��
	// ���꣨��ֵ��
	TCHAR strnum[MAP_SIZE][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") };
	// ���꣨��ĸ��
	TCHAR strabc[MAP_SIZE][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") };
	for (int i = 0; i < MAP_SIZE; i++) {
		outtextxy(75 + number, 35, strnum[i]);
		outtextxy(53, 55 + number, strabc[i]);
		number += BOX_SIZE;
	}
	settextstyle(&nowstyle);
}

// �ж�����i,jλ���ܲ��ܷ�����
bool ChessBoard::canPut(int i, int j, MOUSEMSG mouse) {
	return mouse.x > this->chess[i][j].getX() && mouse.x < this->chess[i][j].getX() + BOX_SIZE//�ж�x����
		&& mouse.y > this->chess[i][j].getY() && mouse.y < this->chess[i][j].getY() + BOX_SIZE//�ж�y����
		&& this->chess[i][j].isEmpty();//�ж��Ƿ��ǿ�λ��
}