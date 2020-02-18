#include "controls.h"

Controls::Controls()
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
}
void Controls::handleEvents(sf::Event& event, World& mWorld)
{
	switch (event.type)
	{
	case::sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case::sf::Keyboard::Space:
			// Do something
			break;
		}
		break;
	}
}
void Controls::handleInputs(World& mWorld)
{
	for (auto pair: mKeyBinding)
	{
		for (int i = 0; i < 4; i++)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			{
				handleKeyboard(pair.first, mWorld);
			}
		}
	}
}

void Controls::handleKeyboard(sf::Keyboard::Key key, World& mWorld)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		mWorld.moveAircraft(-1.f,0);
		break;

	case sf::Keyboard::Right:
		mWorld.moveAircraft(1.f,0);
		break;
	case sf::Keyboard::Up:
		mWorld.moveAircraft(0,-1.f);
		break;
	case sf::Keyboard::Down:
		mWorld.moveAircraft(0,1.f);
		break;
	}
}
bool Controls::isRealtimeAction(Action action)
{
	switch (action)
	{
	case Action::MoveLeft:
	case Action::MoveRight:
	case Action::MoveDown:
	case Action::MoveUp:
		return true;

	default:
		return false;
	}
}