#include "world.h"
#include <iostream>
#include "functions.h" //utility functions library


int World::count = 0;
float World::pressrate = 0;
float World::clickrate = 0; // To limit clicks in a mouse
World::World(sf::RenderWindow& window, int shipId):window(window),shipId(shipId), audioManager(100)
{
	//shipId is to know if the player is host(blue ship) or the client(red ship). id 0 for host, id 1 for client.
	count++;
	loadTextures();
	sf::Cursor cursor;
	if (cursor.loadFromSystem(sf::Cursor::Cross))
		window.setMouseCursor(cursor);
	

	auto blueship = std::make_shared<Spaceship>(0);
	auto redship = std::make_shared<Spaceship>(1);
	spaceships.push_back(blueship);
	spaceships.push_back(redship);

	for (int i = 0; i < 25; i++) {
		asteroids.push_back(std::make_shared<Asteroid>());
	}
	for (int i = 0; i < 10; i++)
	{
		grenades.push_back(std::make_shared<Grenade>());
	}

	finishLine.setTexture(textures.get(Textures::FinishLine));
	float height = window.getSize().x * 2;
	finishLine.setPosition({0,-height});

	velocity = sf::Vector2f();
	acceleration = sf::Vector2f();
	audioManager.load();
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
	updateGrenades();
	checkPickups();
	
	mWorldView.move(0.f, -velocity.y * dt.asSeconds() * 60);
	//How fast the velocity dampens every frame (Handling increases if close to 1.0f)
	velocity *= 0.99f;
}

int World::checkGameStatus()
{
	if (spaceships[shipId]->getBounds().intersects(finishLine.getGlobalBounds()) || spaceships[otherId]->getHealth()<=0)
	{
		return 1;
	}
	else if (spaceships[shipId]->getHealth() <= 0 || spaceships[otherId]->getBounds().intersects(finishLine.getGlobalBounds()))
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
	clickrate++;
	pressrate++;// increases until it reaches 60
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (pressrate > 10)
		{
			audioManager.playSound(SoundEffect::ID::Engine).setVolume(1.5f);
			pressrate = 0;
		}
		velocity += acceleration * time.asSeconds();
	}
	if (clickrate > 30)
	{
		/*handleInputs() function is running at 1/60 sec, so to limit clickrate we execute 
		only when a full second is completed. so mouseclick is 1 click per second*/
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			audioManager.playSound(SoundEffect::ID::PlayerFire);
			// making new bullets and passing to the bullets vector
			auto newbullet = std::make_shared<Bullet>(shipId, spaceships[shipId]->getPosition(), function::normalize(direction));
			bullets.push_back(newbullet);
			isShooting = true;
			clickrate = 0;
		}
	}
	else
	{
		isShooting = false;
	}

}



void World::fireBullets(float speedOfBullet)
{
	for (auto bullet = bullets.begin(); bullet != bullets.end();) {
		if ((*bullet)->isOutOfBounds())
		{
			bullet = bullets.erase(bullet);
		}
		else if ((*bullet)->getId() != otherId && Collision::PixelPerfectTest(spaceships[otherId], *bullet))
		{
			bullet = bullets.erase(bullet);
			spaceships[otherId]->decreaseHealth(10);
		}	
		else if ((*bullet)->getId() == otherId && Collision::PixelPerfectTest(spaceships[shipId], *bullet))
		{
			bullet = bullets.erase(bullet);
			spaceships[shipId]->decreaseHealth(10);
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
			audioManager.playSound(SoundEffect::ID::Explosion);
			pickups.push_back(std::make_shared<Pickup>((*asteroid)->getPosition()));
			asteroid = asteroids.erase(asteroid);
		}
	}
}
void World::updateGrenades() {
	for (auto grenade = grenades.begin(); grenade != grenades.end();) {
		/*float distanceOfGrenadeTravel = 400.f;*/
		//If a certain distance is reached Explode
		if ((*grenade)->getBounds().intersects(spaceships[otherId]->getBounds())||
			(*grenade)->getBounds().intersects(spaceships[shipId]->getBounds()))
		{

			float effectScale = 1000.f;

			auto p = (*grenade)->getPosition();
			for (auto spaceship : spaceships) 
			{
				auto diff = spaceship->getPosition() - p;
				auto effectDampening = 1 / function::magnitude(diff);
				velocity += effectScale * effectDampening * function::normalize(diff);
				//Damage Spaceships here
				//....
			}
			for (auto asteroid : asteroids) 
			{
				auto diff = asteroid->getPosition() - p;

				auto effectDampening = 1 / function::magnitude(diff);
				asteroid->dampingVelocity += 50000.f * effectDampening * function::normalize(diff);
				//Damage Asteroids here
				//....
			}

			grenade = grenades.erase(grenade);

		}
		//else just update normally
		else {
			grenade++;
		}
	}
}
void World::checkPickups()
{
	for (auto pickup = pickups.begin(); pickup != pickups.end();)
	{
		if ((*pickup)->isGrabbed(spaceships[shipId])|| (*pickup)->isGrabbed(spaceships[otherId]))
		{
			audioManager.playSound(SoundEffect::ID::PickUp);
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
			auto otherPos = spaceships[otherId]->getPosition();
			auto thisPos = spaceships[shipId]->getPosition();
			auto diff = otherPos - thisPos;
			//Push back this amount
			velocity += 2.0f * function::normalize(diff);

			//decrease health on collision among spaceships?
			/*spaceships[shipId]->decreaseHealth(1);
			spaceships[otherId]->decreaseHealth(1);*/

			//spaceships[shipId]->setPosition(thisPos - diff / 5.0f);

			//Push other spaceship in the other direction but we have no velocity attribute for other spaceship yet
			spaceships[otherId]->setPosition(otherPos + diff / 5.0f);
		}
	}
	for (auto& asteroid : asteroids)
	{
		if (Collision::PixelPerfectTest(spaceships[shipId], asteroid))
		{
			auto diff = asteroid->getPosition() - spaceships[shipId]->getPosition();
			//spaceships[shipId]->setPosition(spaceships[shipId]->getPosition() - sf::Vector2f{ 20,0 });
			//Push back this amount
			velocity += 3.0f * function::normalize(diff);
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
	for (auto grenade : grenades)
		grenade->render(window);
}

void World::loadTextures()
{
	textures.load(Textures::FinishLine, "Assets/finishline.png");
	if (count==1)
	{
		Grenade::loadTextures();
		Pickup::loadTextures();
		Asteroid::loadTextures();
		Bullet::loadTextures();
	}
}
void World::setOtherPlayers(int other, sf::Vector2f pos, unsigned int h, float angle, bool shoot)
{
	otherId = other;
	spaceships[otherId]->setPosition(pos);
	spaceships[otherId]->setAngle(angle);
	spaceships[otherId]->setHealth(h);

	if (shoot)
	{
		auto a = cos(function::PI / 180 * (angle+90));
		auto b = sin(function::PI / 180 * (angle+90));
		sf::Vector2f dir= { a, b };
		auto newbullet = std::make_shared<Bullet>(otherId, spaceships[otherId]->getPosition(), function::normalize(dir));
		bullets.push_back(newbullet);
	}
}
sf::Packet World::getStatus()
{
	sf::Packet packet;
	float xpos = spaceships[shipId]->getPosition().x;
	float ypos = spaceships[shipId]->getPosition().y;
	float angle = spaceships[shipId]->getAngle();
	unsigned int health = spaceships[shipId]->getHealth();
	packet<< shipId<<  xpos << ypos << angle<<health <<isShooting;
	return packet;
}
