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
private:
	sf::Vector2f getPositionAircraft();
	float firstYPos;
	sf::Time time;
	sf::RenderWindow& window;
	sf::View mWorldView;
	TextureHolder textures;
	std::vector <sf::Sprite> firstPlayerSprite;
	sf::Sprite asteriod;
	sf::Sprite finishLine;
	bool firstPlayer, secondPlayer;
	
};

