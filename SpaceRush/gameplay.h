#pragma once
#include "scene.h"
#include "scenemanager.h"
#include "world.h" 

class GamePlay :
	public Scene
{
public:
    GamePlay(SceneManager& sceneManager, sf::RenderWindow& window, int);
    ~GamePlay();

    void processEvents();
    void update(const sf::Time& dt);
    void draw();
private:
    int shipId;
    World mWorld;
    sf::Sprite bgSprite;
    int gamePlay;
};

