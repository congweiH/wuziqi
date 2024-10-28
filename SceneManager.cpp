#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager() {
    playScene = new PlayScene();

    setScene(playScene);
}

SceneManager::~SceneManager() {
    delete playScene;
}

void SceneManager::setScene(Scene *scene) {
    if (currentScene != nullptr) {
        currentScene->exit();
    }
    currentScene = scene;
    currentScene->enter();
}

void SceneManager::switchScene(SceneManager::SceneType sceneType) {
    currentScene->exit();
    switch (sceneType) {
        case SceneManager::SceneType::PLAY:
            currentScene = playScene;
            break;
    }
    currentScene->enter();
}

void SceneManager::update() {
    currentScene->update();
}

void SceneManager::draw() {
    currentScene->draw();
}

void SceneManager::handleMessage(const ExMessage &msg) {
    currentScene->handleEvent(msg);
}

SceneManager* SceneManager::getInstance() {
    if (!instance) {
        instance = new SceneManager();
    }
    return instance;
}

