#include "world.h"
#include <iostream>
#include "functions.h" //utility functions library
#include "collision.h"

int World::count = 0;
float World::clickrate = 0; // To limit clicks in a mouse
World::World(sf::RenderWindow& window, int shipId):window(window),shipId(shipId)
{
	//shipId is to know if the player is host(blue ship) or the client(red ship). id 0 for host, id 1 for client.
	count++;
	loadTextures();
	sf::Cursor cursor;
	if (cursor.loadFromSystem(sf::Cursor::Cross))
		window.setMouseCursor(cursor);
	for (int i = 0; i < 2; i++)
	{
		if (i == shipId)
			continue;
		otherId = i;
	}

	auto blueship = std::make_shared<Spaceship>(0);
	auto redship = std::make_shared<Spaceship>(1);
	spaceships.push_back(blueship);
	spaceships.push_back(redship);

	/*asteriod.setTexture(textures.get(Textures::Asteriods));
	asteriod.setPosition({100,500});
	asteriod.scale({ 0.3,0.3 });*/

	for (int i = 0; i < 25; i++) {
		asteroids.push_back(std::make_shared<Asteroid>());
	}

	finishLine.setTexture(textures.get(Textures::FinishLine));
	float height = window.getSize().x * 2;
	finishLine.setPosition({0,-height});

	velocity = sf::Vector2f();
	acceleration = sf::Vector2f();

	manageConnection();
}

void World::update(sf::Time dt)
{
	time = dt;

	//Float value to control how fast the spaceship accelerates
	acceleration = 2.f * function::normalize(direction);
	lookAtMouse();
	spaceships[shipId]->move(velocity);
	checkCollision();//checks collision between spaceship and asteriods;
	fireBullets(300.f); //execution code for firing bullet if bullet exists.
	updateAsteroids();
	checkPickups();
	
	mWorldView.move(0.f, -velocity.y * dt.asSeconds() * 60);
	//How fast the velocity dampens every frame (Handling increases if close to 1.0f)
	velocity *= 0.99f;
}

int World::checkGameStatus()
{
	if (spaceships[shipId]->getBounds().intersects(finishLine.getGlobalBounds()))
	{
		return 1;
	}
	else if (spaceships[shipId]->getHealth() <= 0)
	{
		return 2;
	}
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
		if (clickrate > 30)
		{
			// making new bullets and passing to the bullets vector
			auto newbullet = std::make_shared<Bullet>(shipId, spaceships[shipId]->getPosition(), function::normalize(direction));
			bullets.push_back(newbullet);
			clickrate = 0;
		}
	}

}
void World::fireBullets(float speedOfBullet)
{
	//logic for bullet firing. under construction....
	for (auto bullet = bullets.begin(); bullet != bullets.end();) {
		if ((*bullet)->isOutOfBounds())
		{
			bullet = bullets.erase(bullet);
		}
		else if (Collision::PixelPerfectTest(spaceships[otherId], *bullet))
		{
			bullet = bullets.erase(bullet);
			spaceships[otherId]->decreaseHealth(2);
		}
		else if (checkAsteroidCollision(*bullet))
		{
			bullet = bullets.erase(bullet);
		}
		else
		{
			(*bullet)->move(speedOfBullet * (*bullet)->getDirection() * time.asSeconds());
			bullet++;
		}	
	}
	
}
void World::updateAsteroids()
{
	for (auto asteroid = asteroids.begin(); asteroid != asteroids.end();)
	{
		if (!(*asteroid)->isDestroyed())
		{
			(*asteroid)->update(time);
			asteroid++;
		}
		else
		{
			pickups.push_back(std::make_shared<Pickup>((*asteroid)->getPosition()));
			asteroid = asteroids.erase(asteroid);
		}
	}
}
void World::checkPickups()
{
	for (auto pickup = pickups.begin(); pickup != pickups.end();)
	{
		if ((*pickup)->isGrabbed(spaceships[shipId]))
		{
			spaceships[shipId]->setHealth(100);
			pickup = pickups.erase(pickup);
		}
		else
		{
			pickup++;
		}
	}
}
void World::checkCollision()
{
	if (shipId == 0)
	{
		if (Collision::PixelPerfectTest(spaceships[shipId], spaceships[otherId]))
		{
			spaceships[shipId]->setPosition(spaceships[shipId]->getPosition() - sf::Vector2f{ 20,0 });
			spaceships[otherId]->setPosition(spaceships[otherId]->getPosition() + sf::Vector2f{ 20,0 });
		}
	}
	for (auto& asteroid : asteroids)
	{
		if (Collision::PixelPerfectTest(spaceships[shipId], asteroid))
		{
			spaceships[shipId]->setPosition(spaceships[shipId]->getPosition() - sf::Vector2f{ 20,0 });
			spaceships[shipId]->decreaseHealth(1);
		}
	}
	
}
bool World::checkAsteroidCollision(std::shared_ptr<Bullet>& bullet)
{
	for (auto& asteroid : asteroids)
	{
		if (Collision::PixelPerfectTest(asteroid, bullet))
		{
			asteroid->decreaseHealth(1);
			return true;
		}
	}
	return false;
}
void World::draw()
{
	window.setView(mWorldView);
	window.draw(finishLine);
	for (auto spaceship:spaceships)
		spaceship->render(window);
	for (auto bullet : bullets) 
		bullet->render(window);
	for (auto asteroid : asteroids)
		asteroid->render(window);
	for (auto pickup : pickups)
		pickup->render(window);
}

void World::loadTextures()
{
	textures.load(Textures::FinishLine, "Assets/finishline.png");
	if (count==1)
	{
		Asteroid::loadTextures();
		Bullet::loadTextures();
	}
}
void World::manageConnection()
{
	if (shipId == 0)
	{

	}
	else
	{

	}
}
