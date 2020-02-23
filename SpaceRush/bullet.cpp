#include "bullet.h"
#include <iostream>

Bullet::Bullet(int playerid, sf::Vector2f l_shipposition, sf::Vector2f direction)
    :shipId(playerid)
{
    m_direction = direction;
    ship_position = l_shipposition;
    bullet.setPosition(ship_position);
    if (shipId == 0)
    {
       
        bullet.setTexture(bulletTex.get(Textures::BlueBullet));
    }
    if (shipId== 1)
    {
        
        bullet.setTexture(bulletTex.get(Textures::RedBullet));
    }
    bullet.scale({ 0.5,0.5 });
    
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
    if (bullet.getPosition().x > 800 || bullet.getPosition().x < 10)
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