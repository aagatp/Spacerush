#include "pickup.h"
#include "collision.h"

void Pickup::loadTextures()
{
	pickupTex.load(Textures::CollectPickup, "Assets/pickup.png");
	pickupTex.load(Textures::Explosion, "Assets/explosion.png");
}

TextureHolder Pickup::pickupTex;

Pickup::Pickup(sf::Vector2f pos):m_position(pos)
{
	count = 0;
	pickup.setPosition(m_position - sf::Vector2f{100, 100});
}
void Pickup::render(sf::RenderTarget& target)
{
	count++;
	int temp = count/5;
	sf::IntRect rect(temp*256,0, 256, 256);
	if (count > 40)
	{
		pickup.setPosition(m_position);
		pickup.setTexture(pickupTex.get(Textures::CollectPickup));
		pickup.setTextureRect(sf::IntRect(0, 0, 48, 48));
	}
	else
	{
		pickup.setTexture(pickupTex.get(Textures::Explosion));
		pickup.setTextureRect(rect);
	}
	target.draw(pickup);
}
bool Pickup::isGrabbed(std::shared_ptr<Spaceship>& sp)
{
	if (Collision::PixelPerfectTest(sp, pickup))
	{
		return true;
	}
	return false;
}


