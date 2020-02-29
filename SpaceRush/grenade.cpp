#include "grenade.h"
int getRandom(int from, int to) {
	return  rand() % (to - from) + from;
}

void Grenade::loadTextures()
{
	grenadeTex.load(Textures::Grenade, "Assets/grenade.png");
}
Grenade::Grenade()
{
	grenade.setTexture(grenadeTex.get(Textures::Grenade));
	grenade.setOrigin({
			grenade.getGlobalBounds().width / 2 + grenade.getOrigin().x,
			grenade.getGlobalBounds().height / 2 + grenade.getOrigin().y
		});
	grenade.setScale({ 0.3,0.3 });
	position = sf::Vector2f(getRandom(0, 960), getRandom(-3000, 1000));
	grenade.setPosition(position);
}
void Grenade::render(sf::RenderTarget& target)
{
	target.draw(grenade);
}
sf::Vector2f Grenade::getPosition()
{
	return position;
}
sf::FloatRect Grenade::getBounds()
{
	return grenade.getGlobalBounds();
}
TextureHolder Grenade::grenadeTex;