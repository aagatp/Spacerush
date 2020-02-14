#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "scene.h"
#include "gameplay.h"
#include "button.h"
#include "resourceholder.h"

Menu::Menu(SceneManager& sceneManager, sf::RenderWindow& window)
    : Scene(sceneManager, window),currentScreen(MenuScreen::Main),startGame(false), mouseX(0), mouseY(0), isClicked(false), mButtons()
{
	
    window.setMouseCursorVisible(true);
	int screenWidgth = window.getSize().x;
	int screenHeight = window.getSize().y;
	bgTextures.load(Textures::Game, "background.jpg");
    sf::Texture& bgTexture = bgTextures.get(Textures::Game);
	bgTexture.setRepeated(true);
	sf::Vector2i pos(800, 450);
	sf::Vector2i size(1600, 900);
	bgSprite.setTextureRect(sf::IntRect(pos,size));
    bgSprite.setTexture(bgTexture);

	fontholder.load(Fonts::Game, "gamefont.ttf");
    sf::Font& mFont = fontholder.get(Fonts::Game);

	auto playBtn = std::make_shared<Button>();
	playBtn->setAttributes("Play", 24, mFont);
	playBtn->setPos({ 500,500 });
	playBtn->setColor(sf::Color::White);

	auto aboutBtn = std::make_shared<Button>();
	aboutBtn->setAttributes("About", 24, mFont);
	aboutBtn->setPos({ 500,600 });
	aboutBtn->setColor(sf::Color::White);

	auto exitBtn = std::make_shared<Button>();
	exitBtn->setAttributes("Exit", 24, mFont);
	exitBtn->setPos({ 500,700 });
	exitBtn->setColor(sf::Color::White);

	auto joinBtn = std::make_shared<Button>();
	joinBtn->setAttributes("Join Game", 24, mFont);
	joinBtn->setPos({ 800,500 });
	joinBtn->setColor(sf::Color::White);
	
	auto hostBtn = std::make_shared<Button>();
	hostBtn->setAttributes("Host Game", 24, mFont);
	hostBtn->setPos({ 800,600 });
	hostBtn->setColor(sf::Color::White);

	auto backBtn = std::make_shared<Button>();
	backBtn->setAttributes("Back", 24, mFont);
	backBtn->setPos({ 800,700 });
	backBtn->setColor(sf::Color::White);

	mButtons.push_back(playBtn);
	mButtons.push_back(aboutBtn);
	mButtons.push_back(exitBtn);
	mButtons.push_back(joinBtn);
	mButtons.push_back(hostBtn);
	mButtons.push_back(backBtn);

	for (int i = 0; i < 6; i++)
	{
		isSelected[i] = false;
	}
}
Menu::~Menu()
{
}

void Menu::processEvents() {
    sf::Event event;

    if (window.pollEvent(event))
    {
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				mouseX = event.mouseButton.x;
				mouseY = event.mouseButton.y;
				isClicked = true;
			}
			break;
		}
    }
}

void Menu::update(const sf::Time& dt) 
{
	if (startGame == true)
	{
		std::unique_ptr<Scene> gamePlay(new GamePlay(sceneManager, window));
		sceneManager.changeScene(std::move(gamePlay));
	}
	else {
		switch (currentScreen)
		{
		case MenuScreen::Main:
			for (int i = 0; i < 3; i++)
			{
				if (mButtons.at(i)->getGlobalBounds().contains(mouseX, mouseY))
				{
					if (!isSelected[i])
					{
						isSelected[i] = true;
						mButtons.at(i)->setColor(sf::Color::Red);
					}
				}
				else
				{
					if (isSelected[i])
					{
						isSelected[i] = false;
						mButtons.at(i)->setColor(sf::Color::White);
					}
				}
			}

			if (isClicked)
			{
				if (isSelected[0])
				{
					window.setMouseCursorVisible(true);
					currentScreen = MenuScreen::Multiplayer;
				}
				else
				{
					if (isSelected[1])
						currentScreen = MenuScreen::About;
					else
					{
						if (isSelected[2])
							window.close();
					}
				}
				isClicked = false;
			}
			break;

		case MenuScreen::Multiplayer:
			for (int i = 3; i < 6; i++)
			{
				if (mButtons.at(i)->getGlobalBounds().contains(mouseX, mouseY))
				{
					if (!isSelected[i])
					{
						isSelected[i] = true;
						mButtons.at(i)->setColor(sf::Color::Red);
					}
				}
				else
				{
					if (isSelected[i])
					{
						isSelected[i] = false;
						mButtons.at(i)->setColor(sf::Color::White);
					}
				}
			}

			if (isClicked)
			{
				if (isSelected[3])
				{
					window.setMouseCursorVisible(true);
					startGame = true;
				}
				else
				{
					if (isSelected[4])
						startGame = true;
					else
					{
						if (isSelected[5])
							currentScreen = MenuScreen::Main;
					}
				}
				isClicked = false;
			}
			break;

		case MenuScreen::About:
			// About About
			break;
		}
	}
}

void Menu::draw() {
    window.clear(sf::Color::Black);
    window.draw(bgSprite);
    
	switch (currentScreen)
	{
	case MenuScreen::Main:
		for (int i = 0; i < 3; i++)
		{
			mButtons.at(i)->render(window);
		}
		break;
	case MenuScreen::Multiplayer:
		for (int j = 3; j < 6; j++)
		{
			mButtons.at(j)->render(window);
		}
		break;
	case MenuScreen::About:
		break;
	}

    window.display();
}

