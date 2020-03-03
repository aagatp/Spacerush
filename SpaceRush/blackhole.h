#pragma once
#include <SFML/Graphics.hpp>
#include "resourceholder.h"
#include "resourceidentifiers.h"

class Blackhole
{
public:
	sf::Sprite blackhole; 
	sf::Sprite halo;
	Blackhole(int, int);
	void render(sf::RenderWindow& win);

	void update(sf::Time dt);
	sf::FloatRect getBounds();

	sf::IntRect getTextureRect();

	const sf::Texture* getTexture();

	const sf::Transform getInverseTransform();

	sf::Vector2f getPosition();


	static void loadTextures();

	static TextureHolder blackHoleTex;
};

