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

	position = sf::Vector2f(random(0, 960), random(-3000, 0));
	velocity = sf::Vector2f(random(0, 1000) / 1000.f, random(0, 1000) / 1000.f);
	velocity *= 10.f;
	direction = sf::Vector2f(random(0, 1000), random(0, 1000));
	direction = function::normalize(direction);

	asteroid.setScale(scale, scale);
	asteroid.setPosition(position);
	mHealth = 5;

	dampingVelocity = sf::Vector2f();
}


void Asteroid::render(sf::RenderTarget& l_window)
{
	//Draw Sprite
	l_window.draw(asteroid);
}

//void Asteroid::checkBounds()
//{
//	
//}

void Asteroid::update(sf::Time dt)
{
	if (asteroid.getPosition().x <= 100 || asteroid.getPosition().x >= 900 || asteroid.getPosition().y >= 800)
	{
		velocity *= -1.0f;
		asteroid.move(-(velocity + dampingVelocity) * dt.asSeconds());
	}
	else
	{
		asteroid.move(-(velocity + dampingVelocity) * dt.asSeconds());
		asteroid.rotate(angularVelocity * dt.asSeconds());
		dampingVelocity *= 0.999f;
	}

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
}
bool Asteroid::isDestroyed()
{
	if (mHealth <= 0)
		return true;
	return false;
}
const sf::Vector2f Asteroid::getPosition()
{
	return asteroid.getPosition();
}


sf::FloatRect Asteroid::getBounds()
{
	return asteroid.getGlobalBounds();
}
TextureHolder Asteroid::asteriodsTex;

