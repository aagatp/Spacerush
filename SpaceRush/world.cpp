#include "world.h"
#include <iostream>

namespace Utility {
	const float PI = 3.14159265;
	sf::Vector2f normalize(sf::Vector2f& vec) {
		vec *= 1 / sqrt(pow(vec.x, 2) + pow(vec.y, 2));
		return vec;
	}
	float magnitude(sf::Vector2f& vec) { return sqrt(pow(vec.x, 2) + pow(vec.y, 2)); }

}

World::World(sf::RenderWindow& window):window(window),firstPlayer(true),secondPlayer(true)
{
	textures.load(Textures::Asteriods, "Assets/asteriod.png");
	textures.load(Textures::Player1Aircraft, "Assets/player1aircraft.png");
	textures.load(Textures::Player1Fire, "Assets/player1fire.png");
	textures.load(Textures::Player1Missile, "Assets/player1missile.png");
	textures.load(Textures::FinishLine, "Assets/finishline.png");

	firstPlayerSprite.push_back(sf::Sprite((textures.get(Textures::Player1Aircraft))));
	firstPlayerSprite.push_back(sf::Sprite((textures.get(Textures::Player1Fire))));
	firstPlayerSprite.push_back(sf::Sprite((textures.get(Textures::Player1Missile))));

	firstPlayerSprite[0].setOrigin({
			firstPlayerSprite[0].getGlobalBounds().width / 2 + firstPlayerSprite[0].getOrigin().x,
			firstPlayerSprite[0].getGlobalBounds().height / 2 + firstPlayerSprite[0].getOrigin().y
		});


	firstPlayerSprite[0].setPosition({ 500, 500 });
	firstPlayerSprite[0].scale({ 0.3,0.3 });

	asteriod.setTexture(textures.get(Textures::Asteriods));
	asteriod.setPosition({ 100,100 });
	asteriod.scale({ 0.3,0.3 });

	finishLine.setTexture(textures.get(Textures::FinishLine));
	finishLine.setPosition({0,-200});

	velocity = sf::Vector2f();
	acceleration = sf::Vector2f();

}

void World::update(sf::Time dt)
{
	time = dt;
	acceleration = Utility::normalize(direction);
	lookAtMouse(firstPlayerSprite[0]);
	moveAircraft(-velocity.x, -velocity.y);
}

int World::checkGameStatus()
{
	if (firstPlayerSprite[0].getGlobalBounds().intersects(finishLine.getGlobalBounds()) || secondPlayer == false)
		return 1;
	else if (firstPlayer==false)
		return 2;
}

void World::moveAircraft(float x, float y)
{
	firstPlayerSprite[0].move(x, y);
	mWorldView.move(0.f, y *time.asSeconds()*50);
}

//Unused for now
//sf::Vector2f World::getPositionAircraft()
//{
//	return firstPlayerSprite[0].getPosition();
//}

void World::lookAtMouse(sf::Sprite& sprite)
{
	sf::Vector2f curPos = sprite.getPosition();

	sf::Vector2i position = sf::Mouse::getPosition(window);
	position = sf::Vector2i(window.mapPixelToCoords(position, mWorldView));
	direction = sf::Vector2f(curPos.x - position.x, curPos.y - position.y);
	 float rotation = (atan2(direction.y, direction.x)) * 180 / Utility::PI;

	sprite.setRotation(rotation - 90);
	
}

void World::handleInputs(const sf::Time& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity += acceleration * time.asSeconds();
	}
	

}

void World::draw()
{
	window.setView(mWorldView);
	window.draw(finishLine);
	window.draw(firstPlayerSprite[0]);
	window.draw(asteriod);
	window.display();
}