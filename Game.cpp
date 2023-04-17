#include "Game.h"

int dx[4]{ 1, 0, 1, 1 }; // - | \ / �ĸ�����
int dy[4]{ 0, 1, 1, -1 };

TCHAR message[3][20] = { _T("��ʤ"), _T("��ʤ"), _T("ƽ��")};

Game::Game() {
	this->player[0] = new WhitePlayer("����");
	this->player[1] = new BlackPlayer("����");
	this->chessBoard = new ChessBoard();
}

// ��Ϸ��ʼ��
void Game::init() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, NOMINIMIZE);	// ��ʼ�����ڣ�NOMINIMIZE��ʾ��������С��
	setbkcolor(WHITE);					// ���ñ�����ɫ
	setbkmode(TRANSPARENT);				// ����͸�������������
}

// �ȴ��������
bool Game::waitPlayerPutChess(Player* player, int& oldi, int& oldj) {
	while (1) {
		MOUSEMSG mouse = GetMouseMsg(); // ��ȡ�����Ϣ
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				if (this->chessBoard->canPut(i, j, mouse)) {
					// ���ͣ��ĳһ����λ������
					if (mouse.mkLButton) {
						// ���������
						this->total++;						// �������+1
						player->placeChess(chessBoard, i, j);
						oldi = -1;
						oldj = -1;
						return true;
					}
					// ����ѡ���
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
	this->whoWin = -1;// ˭Ӯ��
	this->total = 0;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			this->chessBoard->chess[i][j].setValue(-1);	// ��ʾ��λ��
		}
	}
	cleardevice();
	// ���Ʊ���
	setfillcolor(RGB(255, 205, 150));
	solidrectangle(40, 25, 475, 460);
	// ����������ʽ
	settextstyle(30, 15, 0, 0, 0, 1000, false, false, false);
	settextcolor(BLACK);
	this->chessBoard->show(); // ����
}

// ��ʼ��Ϸ
void Game::play() {
	// ��һ�����ͣ������
	int oldi = 0;
	int oldj = 0;
	// 0 ��������, 1 �������, ��ѭ
	int curPlayerId = 0;
	while (1) {
		// �ȴ���ҷ�����
		if (this->waitPlayerPutChess(this->player[curPlayerId], oldi, oldj)) {
			this->chessBoard->show();
			if (this->isOver(curPlayerId)) {
				// ������ʾ
				MessageBox(GetHWnd(), message[this->whoWin], _T("��Ϸ����"), MB_ICONWARNING);
				break;
			}
			curPlayerId = !curPlayerId;  // 0 �� 1�� 1 �� 0 
		}
	}
}

// �ж���Ϸ�Ƿ����
bool Game::isOver(int playerId) {
	bool isInit = true; // �Ƿ�ոտ���
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (!this->chessBoard->chess[i][j].isEmpty()) {
				// ����ÿ�����ܵ�λ��
				isInit = false;                 // ����У���ô�Ͳ��Ǹոտ���
				int nowcolor = this->chessBoard->chess[i][j].getValue(); // ���ڱ���������ɫ
				int length[4] = { 0, 0, 0, 0 };    // �ĸ�����ĳ���
				for (int k = 0; k < 4; k++) {
					// ԭ��ͬѰ�����λ��
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
					// ���������
					if (length[k] >= 5) {
						this->whoWin = playerId;
					}
				}
				// ȫ�������˶�û��λ����
				if (this->total == MAP_SIZE * MAP_SIZE) {
					this->whoWin = 2; // ƽ��
				}
			}
		}
	}
	if (this->whoWin == -1) {
		// ���û����ʤ��
		Sleep(500);
		return false;
	}
	return true;
}