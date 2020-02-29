#pragma once
#include "scene.h"
#include "scenemanager.h"
#include "world.h" 
#include "server.h"
#include "client.h"

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
    int shipId,otherId;
    World mWorld;
    Client* client;
    Server* server;
    sf::Sprite bgSprite;
    int gamePlay;

};

