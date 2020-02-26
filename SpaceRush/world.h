#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "resourceholder.h"
#include "resourceidentifiers.h"
#include "spaceship.h"
#include "bullet.h"
#include "asteroids.h"
#include "pickup.h"
#include "audio.h"
#include "collision.h"

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



	static int count;
private:
	void checkPickups();
	void checkCollision();
	bool checkAsteroidCollision(std::shared_ptr<Bullet>&);
	void updateAsteroids();
	void fireBullets(float);
	int shipId,otherId;
	void loadTextures();
	sf::View mWorldView;
	sf::Vector2f direction;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Time time;
	TextureHolder textures;

	Audio audioManager;

	std::vector<std::shared_ptr<Spaceship>>spaceships;
	std::vector<std::shared_ptr<Bullet>>bullets;
	std::vector<std::shared_ptr<Asteroid>>asteroids;
	std::vector<std::shared_ptr<Pickup>>pickups;

	//sf::Sprite asteriod;
	sf::Sprite finishLine;	
	static float clickrate;
	static float pressrate;
};

