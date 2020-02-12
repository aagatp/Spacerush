#pragma once
#include "scene.h"
#include "scenemanager.h"
class Menu :public Scene
{
public:
    Menu(SceneManager& sceneManager, sf::RenderWindow& window);
    ~Menu(){}
    void processEvents();
    void update(const sf::Time& dt);
    void draw();
};

