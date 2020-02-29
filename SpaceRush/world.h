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
#include "grenade.h"

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
	sf::Packet getStatus();
	void setOtherPlayers(int,sf::Vector2f,unsigned int, float,bool);
	static int count;
private:
	void checkPickups();
	void checkCollision();
	bool checkAsteroidCollision(std::shared_ptr<Bullet>&);
	void updateAsteroids();
	void updateGrenades();
	void fireBullets(float);
	int shipId,otherId;
	void loadTextures();
	sf::View mWorldView;
	sf::Vector2f direction;
	bool isShooting=false;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Time time;
	TextureHolder textures;

	Audio audioManager;

	std::vector<std::shared_ptr<Spaceship>>spaceships;
	std::vector<std::shared_ptr<Bullet>>bullets;
	std::vector<std::shared_ptr<Asteroid>>asteroids;
	std::vector<std::shared_ptr<Pickup>>pickups;
	std::vector < std::shared_ptr<Grenade>>grenades;

	//sf::Sprite asteriod;
	sf::Sprite finishLine;
	sf::Sprite startLine;
	static float clickrate;
	static float pressrate;
};

