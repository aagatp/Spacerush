#include "pickup.h"
#include "collision.h"

Pickup::Pickup(sf::Vector2f pos):m_position(pos)
{
	pickupTex.load(Textures::CollectPickup, "Assets/pickup.png");
	pickup.setTexture(pickupTex.get(Textures::CollectPickup));
	pickup.setPosition(m_position);
	pickup.scale({ 0.3,0.3 });
}
void Pickup::render(sf::RenderTarget& target)
{
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
