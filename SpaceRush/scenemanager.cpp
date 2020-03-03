#include "scenemanager.h"
#include "scene.h"
#include <iostream>

SceneManager::SceneManager():m_running(true)
{

}

SceneManager::~SceneManager() 
{
    while (!m_scenes.empty()) {
        popScene();
    }
}

void SceneManager::pushScene(std::unique_ptr<Scene> scene) 
{
    m_scenes.push(std::move(scene));
}

void SceneManager::popScene() 
{
    m_scenes.pop();
}

void SceneManager::changeScene(std::unique_ptr<Scene> scene) 
{
    if (!m_scenes.empty()) {
        popScene();
    }
    pushScene(std::move(scene));
}

void SceneManager::processEvents() 
{
    m_scenes.top()->processEvents();
}

void SceneManager::update(sf::Time dt) 
{
    m_scenes.top()->update(dt);
}

void SceneManager::draw() 
{
    m_scenes.top()->draw();
}
std::unique_ptr<Scene> SceneManager::getCurrentState()
{ 
    return std::move(m_scenes.top());
}
bool SceneManager::isRunning()
{
    return m_running; 
}
void SceneManager::quit()
{
    m_running = false;
}
