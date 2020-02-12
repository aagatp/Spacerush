#pragma once
#include "scene.h"
#include "scenemanager.h"
class GamePlay :
	public Scene
{
public:
    GamePlay(SceneManager& sceneManager, sf::RenderWindow& window);
    ~GamePlay();

    void processEvents();
    void update(const sf::Time& dt);
    void draw();
};

