#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "resourceholder.h"
#include "resourceidentifiers.h"
#include "controls.h"
class World
{
public:
	World(sf::RenderWindow& window);
	void draw();
	void update(sf::Time dt);
	int checkGameStatus();
	void moveAircraft(float x, float y);
	sf::RenderWindow& window;
private:
	sf::Vector2f getPositionAircraft();
	sf::Time time;
	//void lookAtMouse(sf::Sprite& sprite);
	sf::View mWorldView;
	TextureHolder textures;
	std::vector <sf::Sprite> firstPlayerSprite;
	sf::Sprite asteriod;
	sf::Sprite finishLine;
	bool firstPlayer, secondPlayer;
	
};

