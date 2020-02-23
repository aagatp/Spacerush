#include "world.h"
#include <iostream>
#include "functions.h" //utility functions library

float World::clickrate = 0; // To limit clicks in a mouse
World::World(sf::RenderWindow& window, int shipId):window(window),shipId(shipId)
{
	//shipId is to know if the player is host(blue ship) or the client(red ship). id 0 for host, id 1 for client.
	textures.load(Textures::Asteriods, "Assets/asteriod.png");
	textures.load(Textures::FinishLine, "Assets/finishline.png");
	
	Bullet::loadTextures();

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
	
	fireBullets(); //execution code for firing bullet if bullet exists.

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
	clickrate++; // increases until it reaches 60
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity += acceleration * time.asSeconds();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		/*handleInputs() function is running at 1/60 sec, so to limit clickrate we execute 
		only when a full second is completed. so mouseclick is 1 click per second*/
		if (clickrate > 60)
		{
			// making new bullets and passing to the bullets vector
			auto newbullet = std::make_shared<Bullet>(shipId, spaceships[shipId]->getPosition(), function::normalize(direction));
			bullets.push_back(newbullet);
			clickrate = 0;
		}
	}

}
void World::fireBullets()
{
	//logic for bullet firing. under construction....
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
}