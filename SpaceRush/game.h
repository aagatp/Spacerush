#pragma once
#include <SFML/Graphics.hpp>
#include "scenemanager.h"

class Game
{
public:
	Game();
	void run();
	void processInput();
	void render();
	void update(sf::Time dt);
private:
	static const sf::Time timePerFrame;
	sf::RenderWindow window;
	SceneManager sceneManager;
};