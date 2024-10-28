#pragma once

#include <graphics.h>

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;
    virtual void handleEvent(const ExMessage& msg) = 0;
};
