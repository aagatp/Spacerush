#include "world.h"
#include <iostream>
#include "functions.h"

float World::clickrate = 0;
World::World(sf::RenderWindow& window, int shipId):window(window),shipId(shipId)
{
	textures.load(Textures::Asteriods, "Assets/asteriod.png");
	textures.load(Textures::FinishLine, "Assets/finishline.png");
	
	auto blueship = std::make_shared<Spaceship>(0);
	auto redship = std::make_shared<Spaceship>(1);
	spaceships.push_back(blueship);
	spaceships.push_back(redship);

	asteriod.setTexture(textures.get(Textures::Asteriods));
	asteriod.setPosition({100,500});
	asteriod.scale({ 0.3,0.3 });

	finishLine.setTexture(textures.get(Textures::FinishLine));
	finishLine.setPosition({0,-200});

	velocity = sf::Vector2f();
	acceleration = sf::Vector2f();
}

void World::update(sf::Time dt)
{
	time = dt;
	acceleration = function::normalize(direction);
	lookAtMouse();
	spaceships[shipId]->move(velocity);
	fireBullets();

	//Damp velocity Every frame
	velocity *= 0.99f;

	mWorldView.move(0.f, -velocity.y * dt.asSeconds() * 50);
}

int World::checkGameStatus()
{
	if (spaceships[shipId]->getBounds().intersects(finishLine.getGlobalBounds()))
		return 1;
	else if (spaceships[shipId]->getHealth()<=0)
		return 2;
}

void World::lookAtMouse()
{
	sf::Vector2f curPos = spaceships[shipId]->getPosition();
	sf::Vector2i position = sf::Mouse::getPosition(window);
	position = sf::Vector2i(window.mapPixelToCoords(position,mWorldView));
	direction = sf::Vector2f(curPos.x - position.x, curPos.y - position.y);
	float rotation = (atan2(direction.y, direction.x)) * 180 / function::PI;
	spaceships[shipId]->setAngle(rotation - 90);
}

void World::handleInputs()
{
	clickrate++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity += acceleration * time.asSeconds();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (clickrate > 60)
		{
			auto newbullet = std::make_shared<Bullet>(shipId, spaceships[shipId]->getPosition(), function::normalize(direction));
			bullets.push_back(newbullet);
			clickrate = 0;
		}
	}

}
void World::fireBullets()
{
	for (auto bullet = bullets.begin(); bullet != bullets.end();) {
		if ((*bullet)->isOutOfBounds())
			bullet = bullets.erase(bullet);
		else
		{
			(*bullet)->move(100.f * (*bullet)->getDirection() * time.asSeconds());
			bullet++;
		}
	}
}
void World::draw()
{
	window.setView(mWorldView);
	window.draw(finishLine);
	for (auto spaceship:spaceships)
		spaceship->render(window);
	for (auto bullet : bullets) 
		bullet->render(window);
	window.draw(asteriod);
	window.display();
}