#pragma once
#include "spaceship.h"
#include <SFML/Graphics.hpp>
class Pickup
{
public:
	Pickup(sf::Vector2f);
	void render(sf::RenderTarget& target);
	bool isGrabbed(std::shared_ptr<Spaceship>& spaceship);
	static void loadTextures(); 
	sf::IntRect getTextureRect();
	const sf::Texture* getTexture();
	const sf::Transform getInverseTransform();
	sf::FloatRect getBounds();



private:
	int count;
	static TextureHolder pickupTex;
	sf::Vector2f m_position;
	sf::Sprite pickup;
};

