#pragma once
#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();
	void run();
	void processInputs();
	void render();
	void update();
private:
	sf::RenderWindow window;
};