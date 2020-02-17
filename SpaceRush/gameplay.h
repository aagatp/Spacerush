#pragma once
#include "scene.h"
#include "scenemanager.h"
#include "world.h" 
#include "controls.h"
class GamePlay :
	public Scene
{
public:
    GamePlay(SceneManager& sceneManager, sf::RenderWindow& window);
    ~GamePlay();

    void processEvents();
    void update(const sf::Time& dt);
    void draw();
private:
    World mWorld;
    Controls mControl;
    sf::Sprite bgSprite;
    int gamePlay;
};

