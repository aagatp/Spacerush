#pragma once
#include "scenemanager.h"
#include "world.h"
class Controls
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
	};
	Controls();
	void handleEvents(sf::Event& event, World& mWorld);
	void handleInputs(World& mWorld);
private:
	
	void handleKeyboard(sf::Keyboard::Key, World& mWorld);
	bool isRealtimeAction(Action action);
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
};

