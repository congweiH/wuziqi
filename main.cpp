#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <string>
#include <cstring>
#include "Game.h"

using namespace std;


// main函数
int main() {
	Game* game = new Game();
	game->init(); // 初始化
	
	while (1) {
		game->draw();	// 游戏绘制
		game->play();	// 开始游戏
	}
}