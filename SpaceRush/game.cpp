#include "game.h"
#include <SFML/Graphics.hpp>
#include "scenestates.h"
#include "menu.h"


Game::Game():window(sf::VideoMode(1800,960), "Space Rush")
{
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	std::unique_ptr<Scene> menu(new Menu(sceneManager, window));
	sceneManager.changeScene(std::move(menu));
}
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (sceneManager.isRunning())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			processInput();
			update(timePerFrame);
		}
		render();
	}

}

void Game::processInput()
{
	sceneManager.processEvents();
}

void Game::render()
{
	sceneManager.draw();
	window.setView(window.getDefaultView());

}
void Game::update(sf::Time dt)
{
	sceneManager.update(dt);
}
