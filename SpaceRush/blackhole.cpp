#include "blackhole.h"

Blackhole::Blackhole(int x, int y)
{

	halo.setTexture(blackHoleTex.get(Textures::Halo));
	halo.setPosition(x, y);
	halo.setOrigin({
		halo.getGlobalBounds().width / 2 + halo.getOrigin().x,
		halo.getGlobalBounds().height / 2 + halo.getOrigin().y
		});

	blackhole.setTexture(blackHoleTex.get(Textures::BlackHole));
	blackhole.setOrigin({
			blackhole.getGlobalBounds().width / 2 + blackhole.getOrigin().x,
			blackhole.getGlobalBounds().height / 2 + blackhole.getOrigin().y
		});
	blackhole.setPosition(halo.getPosition());
	blackhole.setScale(0.3, 0.3);
	halo.setScale(0.3, 0.3);
}

void Blackhole::render(sf::RenderWindow& win)
{
	win.draw(halo);
	win.draw(blackhole);
}

void Blackhole::update(sf::Time dt)
{
	if (halo.getScale().x < 0.6f)
		halo.scale(2.0f, 2.0f);
	halo.scale(0.99f, 0.99f);
}

void Blackhole::loadTextures()
{
	static int t = 0;
	if (t == 0) {
		blackHoleTex.load(Textures::BlackHole, "Assets/blackhole.png");
		blackHoleTex.load(Textures::Halo, "Assets/halo.png");
		t++;
	}
}

sf::FloatRect Blackhole::getBounds()
{
	return halo.getGlobalBounds();
}

sf::IntRect Blackhole::getTextureRect()
{
	return halo.getTextureRect();
}

const sf::Texture* Blackhole::getTexture()
{
	return halo.getTexture();
}

const sf::Transform Blackhole::getInverseTransform()
{
	return halo.getInverseTransform();
}

sf::Vector2f Blackhole::getPosition() { return blackhole.getPosition(); }


TextureHolder Blackhole::blackHoleTex;
