#include "bullet.h"
#include <iostream>

Bullet::Bullet(int playerid, sf::Vector2f l_shipposition, sf::Vector2f direction)
	:shipId(playerid)
{
	yAxisLife = 0;
	m_direction = direction;
	ship_position = l_shipposition;
	bullet.setPosition(ship_position);
	if (shipId == 0)
	{
		bullet.setTexture(bulletTex.get(Textures::BlueBullet));
	}
	if (shipId == 1)
	{
		bullet.setTexture(bulletTex.get(Textures::RedBullet));
	}

	bullet.setOrigin({
			bullet.getGlobalBounds().width / 2 + bullet.getOrigin().x,
			bullet.getGlobalBounds().height / 2 + bullet.getOrigin().y
		});

	bullet.scale({ 0.7,0.7 });

	bullet.setRotation((atan2(direction.y, direction.x)) * 180 / 3.14159265 - 90);
}
Bullet::~Bullet()
{
}

void Bullet::setPosition(sf::Vector2f initial_position)
{
	bullet.setPosition(initial_position);
}

void Bullet::move(sf::Vector2f position)
{
	yAxisLife++;
	bullet.move(-position);
}

sf::Vector2f Bullet::getPosition()
{
	return bullet.getPosition();
}

sf::Vector2f Bullet::getDirection()
{
	return m_direction;
}
bool Bullet::isOutOfBounds()
{
	if (bullet.getPosition().x > 960|| bullet.getPosition().x < 5 || yAxisLife>1000)
	{
		return true;
	}
	return false;
}

void Bullet::loadTextures()
{
	bulletTex.load(Textures::BlueBullet, "Assets/bluebullet.png");
	bulletTex.load(Textures::RedBullet, "Assets/redbullet.png");
}

TextureHolder Bullet::bulletTex;

void Bullet::render(sf::RenderTarget& l_window)
{
	l_window.draw(bullet);
}

sf::FloatRect Bullet::getBounds()
{
	return bullet.getGlobalBounds();
}
sf::IntRect Bullet::getTextureRect()
{
	return bullet.getTextureRect();
}
const sf::Texture* Bullet::getTexture()
{
	return bullet.getTexture();
}
const sf::Transform Bullet::getInverseTransform()
{
	return bullet.getInverseTransform();
}