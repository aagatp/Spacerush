#pragma once
#include <SFML/Graphics.hpp>
#include "resourceidentifiers.h"
#include "resourceholder.h"
class Grenade
{
public:
	static void loadTextures();
	Grenade();
	void render(sf::RenderTarget& target);
	//void update(sf::Time dt);
	sf::Vector2f getPosition();
	sf::FloatRect getBounds();
private:
	static TextureHolder grenadeTex;
	sf::Sprite grenade;
	sf::Vector2f position;

};

