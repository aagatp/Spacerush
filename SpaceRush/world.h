#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "resourceholder.h"
#include "resourceidentifiers.h"
#include "spaceship.h"
#include "bullet.h"

class World
{
public:
	World(sf::RenderWindow& window, int shipId);
	void draw();
	void update(sf::Time dt);
	int checkGameStatus();
	void lookAtMouse();
	sf::RenderWindow& window;
	void handleInputs();
private:
	void fireBullets();
	int shipId;
	sf::View mWorldView;
	sf::Vector2f direction;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Time time;
	TextureHolder textures;
	std::vector<std::shared_ptr<Spaceship>>spaceships;
	std::vector<std::shared_ptr<Bullet>>bullets;
	sf::Sprite asteriod;
	sf::Sprite finishLine;	
	static float clickrate;
};

