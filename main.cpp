#include "Game.h"

using namespace std;

int main() {
    Game* game = new Game();

    // 设置帧率，例如 144 帧每秒
    int fps = 144;
    // 计算每帧之间的时间间隔，以毫秒为单位
    int interval = 1000 / fps;

    while (game->running) {
        game->update();
        game->draw();	// 游戏绘制

        // 暂停一段时间，以控制帧率
        Sleep(interval);
    }
}