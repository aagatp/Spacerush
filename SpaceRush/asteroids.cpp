#include "asteroids.h"
#include "functions.h"

int random(int from, int to) {
	return  rand() % (to - from) + from;
}

void Asteroid::loadTextures()
{
	asteriodsTex.load(Textures::Asteroids, "Assets/asteroid.png");
}


Asteroid::Asteroid() {
	asteroid.setTexture(asteriodsTex.get(Textures::Asteroids));
	asteroid.setOrigin({
			asteroid.getGlobalBounds().width / 2 + asteroid.getOrigin().x,
			asteroid.getGlobalBounds().height / 2 + asteroid.getOrigin().y
		});

	//srand(time(0));
	angularVelocity = static_cast<float> (random(-100, 100));
	scale = static_cast<float> (random(25, 50));
	scale /= 100;

	position = sf::Vector2f(random(0, 1000), random(0, 1000));
	velocity = sf::Vector2f(random(0, 1000) / 1000.f, random(0, 1000) / 1000.f);
	velocity *= 10.f;
	direction = sf::Vector2f(random(0, 1000), random(0, 1000));
	direction = function::normalize(direction);

	asteroid.setScale(scale, scale);
	asteroid.setPosition(position);
	mHealth = 5;
}


void Asteroid::render(sf::RenderTarget& l_window)
{
	//Draw Sprite
	l_window.draw(asteroid);
}

void Asteroid::update(sf::Time dt)
{
	position += velocity * dt.asSeconds();
	asteroid.setPosition(position);
	asteroid.rotate(angularVelocity * dt.asSeconds());
}
sf::IntRect Asteroid::getTextureRect()
{
	return asteroid.getTextureRect();
}
const sf::Texture* Asteroid::getTexture()
{
	return asteroid.getTexture();
}
const sf::Transform Asteroid::getInverseTransform()
{
	return asteroid.getInverseTransform();
}

void Asteroid::decreaseHealth(int a)
{
	mHealth = mHealth - a;
	//if (mHealth <= 0)
	//{
	//	//destroy to create pickup.
	//}
}

sf::FloatRect Asteroid::getBounds()
{
	return asteroid.getGlobalBounds();
}
TextureHolder Asteroid::asteriodsTex;

