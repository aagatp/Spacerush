#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "resourceholder.h"
#include "resourceidentifiers.h"

class World
{
public:
	World(sf::RenderWindow& window);
	void draw();
	void update(sf::Time dt);
	int checkGameStatus();
	void moveAircraft(float x, float y);
	void lookAtMouse(sf::Sprite&);
	sf::RenderWindow& window;
	void handleInputs(const sf::Time& dt);
private:
	//sf::Vector2f getPositionAircraft();

	sf::Vector2f direction;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	sf::Time time;
	
	sf::View mWorldView;
	TextureHolder textures;
	std::vector <sf::Sprite> firstPlayerSprite;
	sf::Sprite asteriod;
	sf::Sprite finishLine;
	bool firstPlayer, secondPlayer;
	
};

