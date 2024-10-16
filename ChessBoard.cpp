#include "ChessBoard.h"

// 画棋盘
void ChessBoard::draw() {
    offsetX = 40;
    offsetY = 40;
    int expandWidth = 40;
    // 绘制底色
    setfillcolor(RGB(255, 205, 150));
    solidrectangle(0 + offsetX - expandWidth, 0 + offsetY - expandWidth, BOX_COUNT * BOX_WIDTH + offsetX + expandWidth, BOX_COUNT * BOX_WIDTH + offsetY + expandWidth);

    // 绘制线条
    setlinecolor(BLACK);
    // 绘制四周的线条，要粗一些
    setlinestyle(PS_SOLID, 3);
    line(0 + offsetX, 0 + offsetY, BOX_COUNT * BOX_WIDTH + offsetX, 0 + offsetY);
    line(0 + offsetX, BOX_COUNT * BOX_WIDTH + offsetY, BOX_COUNT * BOX_WIDTH + offsetX, BOX_COUNT * BOX_WIDTH + offsetY);
    line(0 + offsetX, 0 + offsetY, 0 + offsetX, BOX_COUNT * BOX_WIDTH + offsetY);
    line(BOX_COUNT * BOX_WIDTH + offsetX, 0 + offsetY, BOX_COUNT * BOX_WIDTH + offsetX, BOX_COUNT * BOX_WIDTH + offsetY);
    // 绘制中间的线条
    setlinestyle(PS_SOLID, 2);
    for (int i = 1; i < BOX_COUNT; i++) {
        // 横线
        line(0 + offsetX, i * BOX_WIDTH + offsetY, BOX_COUNT * BOX_WIDTH + offsetX, i * BOX_WIDTH + offsetY);
        // 竖线
        line(i * BOX_WIDTH + offsetX, 0 + offsetY, i * BOX_WIDTH + offsetX, BOX_COUNT * BOX_WIDTH + offsetY);
    }

    // 绘制圆点
    setfillcolor(BLACK);
    fillcircle(3 * BOX_WIDTH + offsetX, 3 * BOX_WIDTH + offsetY, 4);
    fillcircle(3 * BOX_WIDTH + offsetX, 9 * BOX_WIDTH + offsetY, 4);
    fillcircle(9 * BOX_WIDTH + offsetX, 3 * BOX_WIDTH + offsetY, 4);
    fillcircle(9 * BOX_WIDTH + offsetX, 9 * BOX_WIDTH + offsetY, 4);
    fillcircle(6 * BOX_WIDTH + offsetX, 6 * BOX_WIDTH + offsetY, 4);

    // 绘制文字
    settextcolor(BLACK);
    int number = - BOX_WIDTH / 2 + 7; // 调试得到的
	// 坐标（数值）
	TCHAR strNum[BOX_COUNT + 1][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") };
	// 坐标（字母）
	TCHAR strAbc[BOX_COUNT + 1][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") };
	for (int i = 0; i < BOX_COUNT + 1; i++) {
		outtextxy(offsetX + number, offsetY - 18 - BOX_WIDTH / 2, strNum[i]);
		outtextxy(offsetX - 15 - BOX_WIDTH / 2, offsetY + number, strAbc[i]);
		number += BOX_WIDTH;
	}

    // 绘制棋子
    setlinestyle(PS_SOLID, 1);
    for (int i = 0; i < BOX_COUNT + 1; i++) {
        for (int j = 0; j < BOX_COUNT + 1; j++) {
            // 白棋
            if (chess[i][j] == 1) {
                setfillcolor(WHITE);
                fillcircle(i * BOX_WIDTH + offsetX, j * BOX_WIDTH + offsetY, 13);
            } else if (chess[i][j] == -1) {
                setfillcolor(BLACK);
                fillcircle(i * BOX_WIDTH + offsetX, j * BOX_WIDTH + offsetY, 13);
            }

        }
    }

    // 绘制鼠标选中的位置
    if (aimX != -1) {
        setlinestyle(PS_SOLID, 2);
        setlinecolor(LIGHTGRAY);
        int x = aimX * BOX_WIDTH + offsetX - BOX_WIDTH / 2;
        int y = aimY * BOX_WIDTH + offsetY - BOX_WIDTH / 2;
        line(x + 1, y + 2, x + 8, y + 2);
        line(x + 2, y + 1, x + 2, y + 8);
        line(x + 28, y + 2, x + 22, y + 2);
        line(x + 28, y + 1, x + 28, y + 8);
        line(x + 2, y + 28, x + 8, y + 28);
        line(x + 2, y + 22, x + 2, y + 28);
        line(x + 28, y + 28, x + 22, y + 28);
        line(x + 28, y + 22, x + 28, y + 28);
    }
}

void ChessBoard::reset() {
    player = 1; // 白棋先手
    for (int i = 0; i < BOX_COUNT + 1; i++) {
        for (int j = 0; j < BOX_COUNT + 1; j++) {
            chess[i][j] = 0;	// 表示空位置
        }
    }
}

void ChessBoard::putWhiteChess(int i, int j) {
    chess[i][j] = 1;
}

void ChessBoard::putBlackChess(int i, int j) {
    chess[i][j] = -1;
}

void ChessBoard::pollEvents(const ExMessage &msg) {
    if (msg.message == WM_MOUSEMOVE) {
        int i = -1;
        int j = -1;
        bool inSide = pixelToChess(msg.x, msg.y, i, j);
        if (inSide) {
            aimX = i;
            aimY = j;
        } else {
            aimX = -1;
            aimY = -1;
        }
    }
    if (msg.message == WM_LBUTTONDOWN) {
        int i = -1;
        int j = -1;
        bool inSide = pixelToChess(msg.x, msg.y, i, j);
        if (inSide && canPut(i, j)) {
            putChess(i, j);
        }
    }
}

void ChessBoard::putChess(int i, int j) {
    if (player == 1) {
        putWhiteChess(i, j);
    } else {
        putBlackChess(i, j);
    }
    player = -player;
}

bool ChessBoard::pixelToChess(int x, int y, int &i, int &j) const {
    x = x - offsetX + BOX_WIDTH / 2;
    y = y - offsetY + BOX_WIDTH / 2;
    i = x / BOX_WIDTH;
    j = y / BOX_WIDTH;
    if (x < 0 || x > BOX_COUNT * BOX_WIDTH + BOX_WIDTH || y < 0 || y > BOX_COUNT * BOX_WIDTH + BOX_WIDTH) {
        return false;
    }
    return true;
}

int ChessBoard::hasWinner() {
    for (int row = 0; row < BOX_COUNT + 1; ++row) {
        for (int col = 0; col < BOX_COUNT + 1; ++col) {
            if (chess[row][col] == 0) continue;

            // 检查水平方向
            if (checkLine(row, col, 0, 1)) return -player;
            // 检查垂直方向
            if (checkLine(row, col, 1, 0)) return -player;
            // 检查正对角线方向
            if (checkLine(row, col, 1, 1)) return -player;
            // 检查反对角线方向
            if (checkLine(row, col, 1, -1)) return -player;
        }
    }
    return 0;
}

bool ChessBoard::checkLine(int i, int j, int dx, int dy) {
    int count = 0;
    char currentPiece = chess[i][j];
    for (int c = 0; c < 5; ++c) {
        int newRow = i + dx * c;
        int newCol = j + dy * c;
        if (newRow >= 0 && newRow < BOX_COUNT + 1 && newCol >= 0 && newCol < BOX_COUNT + 1 &&
            chess[newRow][newCol] == currentPiece) {
            ++count;
        } else {
            return false;
        }
    }
    return count == 5;
}

bool ChessBoard::canPut(int i, int j) {
    return chess[i][j] == 0;
}
