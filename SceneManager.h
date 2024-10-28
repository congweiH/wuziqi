#pragma once

#include "Scene.h"
#include "PlayScene.h"

// 单例模式
class SceneManager {
public:
    enum class SceneType {
        PLAY,
    };

public:
    SceneManager();
    ~SceneManager();

    // 禁止拷贝和赋值操作
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    void setScene(Scene* scene);
    void switchScene(SceneType sceneType);
    void update();
    void draw();
    void handleMessage(const ExMessage& msg);

    static SceneManager* getInstance();

    static SceneManager* instance; // 静态实例指针
    Scene* currentScene = nullptr;

    Scene* playScene;  // 玩家场景
};
