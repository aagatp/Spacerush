#include "pickup.h"
#include "collision.h"

//void Pickup::loadTextures()
//{
//	//Not Working
//}

Pickup::Pickup(sf::Vector2f pos):m_position(pos)
{
	pickupTex.load(Textures::CollectPickup, "Assets/pickup.png");
	pickupTex.load(Textures::Explosion, "Assets/explosion.png");
	count = 0;
	pickup.setPosition(m_position - sf::Vector2f{100, 100});
}
void Pickup::render(sf::RenderTarget& target)
{
	count++;
	if (count > 40)
	{
		pickup.setPosition(m_position);
		pickup.setTexture(pickupTex.get(Textures::CollectPickup));
	}
	else
	{
		pickup.setTexture(pickupTex.get(Textures::Explosion));
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

