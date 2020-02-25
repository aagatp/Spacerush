#pragma once
#include "spaceship.h"
#include <SFML/Graphics.hpp>
class Pickup
{
public:
	Pickup(sf::Vector2f);
	void render(sf::RenderTarget& target);
	bool isGrabbed(std::shared_ptr<Spaceship>& spaceship);
	//static void loadTextures();  Not working
private:
	int count;
	/*static TextureHolder pickupTex;*/ //Not working
	TextureHolder pickupTex;
	sf::Vector2f m_position;
	sf::Sprite pickup;
};

