#include "grenade.h"
#include "functions.h"


TextureHolder Grenade::grenadeTex;

Grenade::Grenade(int playerid, sf::Vector2f l_shipposition, sf::Vector2f direction)
	:texId(playerid), position(l_shipposition)
{
	
	if (texId == 0)
		grenade.setTexture(grenadeTex.get(Textures::BlueMissile));
	if (texId == 1)
		grenade.setTexture(grenadeTex.get(Textures::RedMissile));
	

	grenade.setOrigin({
			grenade.getGlobalBounds().width / 2 + grenade.getOrigin().x,
			grenade.getGlobalBounds().height / 2 + grenade.getOrigin().y
		});

	grenade.scale({ 0.3f, 0.3f });

	grenade.setPosition(position);
	velocity = function::normalize(direction);
}
void Grenade::render(sf::RenderTarget& l_window)
{
	l_window.draw(grenade);
}



void Grenade::loadTextures()
{
	static bool firstLoad = true;
	if (firstLoad) { 
		grenadeTex.load(Textures::BlueMissile, "Assets/bluemissile.png"); 
		grenadeTex.load(Textures::RedMissile, "Assets/bluemissile.png"); 
		firstLoad = false;
	}
}

void Grenade::move(sf::Vector2f position)
{
	grenade.move(-position);
}

void Grenade::rotate(float angle)
{
	grenade.rotate(angle);
}
