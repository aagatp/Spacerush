#pragma once
#include <stack>
#include <memory>

#include "scene.h"

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void pushScene(std::unique_ptr<Scene> scene);
    void popScene();
    void changeScene(std::unique_ptr<Scene> scene);

    void processEvents();
    void update(sf::Time dt);
    void draw();

    std::unique_ptr<Scene> getCurrentState();

    bool isRunning();
    void quit();
private:
    std::stack<std::unique_ptr<Scene>> m_scenes;
    bool m_running;
};