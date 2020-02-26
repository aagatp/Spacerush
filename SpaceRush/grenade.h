#pragma once

#include <SFML/Graphics.hpp>
#include "resourceidentifiers.h"
#include "resourceholder.h"

class Grenade
{
private:
	static TextureHolder grenadeTex;
	int texId;
	sf::Sprite grenade;
public:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f distanceTravelled;

public:

	Grenade(int playerid, sf::Vector2f l_shipposition, sf::Vector2f direction);
	static void loadTextures();
	void render(sf::RenderTarget& l_window);
	void move(sf::Vector2f);
	void rotate(float);
};

