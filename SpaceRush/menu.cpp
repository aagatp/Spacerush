#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "menu.h"
#include "scene.h"
#include "gameplay.h"
#include "resourceholder.h"


Menu::Menu(SceneManager& sceneManager, sf::RenderWindow& window)
    : Scene(sceneManager, window),currentScreen(MenuScreen::Main),startGame(false), mouseX(0), mouseY(0), isClicked(false), mButtons(), audiomanager(100)
{
	audiomanager.loadMenu();
    window.setMouseCursorVisible(true);
	float screenWidgth = window.getSize().x;
	float screenHeight = window.getSize().y;
	
    sf::Texture& bgTexture = bgTextures.get(Textures::Space);
	bgTexture.setRepeated(true);
	sf::Vector2i pos(screenWidgth/2, screenHeight/2);
	sf::Vector2i size(screenWidgth,screenHeight);
	bgSprite.setTextureRect(sf::IntRect(pos,size));
    bgSprite.setTexture(bgTexture);
    sf::Font& mFont = fontholder.get(Fonts::Game);

	auto playBtn = std::make_shared<Button>();
	playBtn->setAttributes("Play", 40, mFont);
	playBtn->setPos({ screenWidgth/2-playBtn->getSize()/2,600 });
	playBtn->setColor(sf::Color::White);

	auto aboutBtn = std::make_shared<Button>();
	aboutBtn->setAttributes("About", 40, mFont);
	aboutBtn->setPos({ screenWidgth / 2-aboutBtn->getSize() / 2,700 });
	aboutBtn->setColor(sf::Color::White);

	auto exitBtn = std::make_shared<Button>();
	exitBtn->setAttributes("Exit", 40, mFont);
	exitBtn->setPos({ screenWidgth / 2-exitBtn->getSize() / 2,800 });
	exitBtn->setColor(sf::Color::White);

	auto joinBtn = std::make_shared<Button>();
	joinBtn->setAttributes("Join Game", 40, mFont);
	joinBtn->setPos({ screenWidgth / 2 - joinBtn->getSize() / 2,700 });
	joinBtn->setColor(sf::Color::White);
	
	auto hostBtn = std::make_shared<Button>();
	hostBtn->setAttributes("Host Game", 40, mFont);
	hostBtn->setPos({ screenWidgth / 2 - hostBtn->getSize() / 2, 600 });
	hostBtn->setColor(sf::Color::White);
	
	auto backBtn = std::make_shared<Button>();
	backBtn->setAttributes("Back", 40, mFont);
	backBtn->setPos({ screenWidgth-100-backBtn->getSize(),screenHeight-100});
	backBtn->setColor(sf::Color::White);

	auto joinPlay = std::make_shared<Button>();
	joinPlay->setAttributes("Play", 40, mFont);
	joinPlay->setPos({ screenWidgth / 2 - playBtn->getSize() / 2,900 });
	joinPlay->setColor(sf::Color::White);

	mButtons.push_back(playBtn);
	mButtons.push_back(aboutBtn);
	mButtons.push_back(exitBtn);
	mButtons.push_back(hostBtn);
	mButtons.push_back(joinBtn);
	mButtons.push_back(backBtn);
	mButtons.push_back(joinPlay);

	auto titleText = std::make_shared<TextBox>();
	titleText->setAttributes("Space Rush", 100, mFont);
	titleText->setPos({ screenWidgth / 2 - titleText->getSize()/2,250 });
	titleText->setColor(sf::Color::Red);
	
	auto readText = std::make_shared<TextBox>();
	readText->setAttributes("The game involves a race between two Spaceships",35, mFont);
	readText->setPos({100,700});
	readText->setColor(sf::Color::White);

	auto creditsText = std::make_shared<TextBox>();
	readText->setAttributes("Developed with lots of love and code.", 35, mFont);
	readText->setPos({ 100,800});
	readText->setColor(sf::Color::White);

	mTextBox.push_back(titleText);
	mTextBox.push_back(readText);
	mTextBox.push_back(creditsText);

	auto entry = std::make_shared<EntryBox>();
	entry->setAttributes(mFont);
	entry->setPos({ screenWidgth / 2 - joinBtn->getSize() / 2,800 });
	entrybox = entry;

	for (int i = 0; i < 7; i++)
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
			//window.close();
			sceneManager.quit();
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
		//shipId is 0 if game is hosted and 1 if it is joined.
		std::unique_ptr<Scene> gamePlay(new GamePlay(sceneManager, window, shipId));
		sceneManager.changeScene(std::move(gamePlay));
	}
	else 
	{
		switch (currentScreen)
		{
		case MenuScreen::Main:
			for (int i = 0; i < 3; i++)
			{
				if (mButtons.at(i)->getGlobalBounds().contains(mouseX, mouseY))
				{
					if (!isSelected[i])
					{
						audiomanager.playSound(SoundEffect::Select);
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
							sceneManager.quit();
					}
				}
				isClicked = false;
			}
			break;

		case MenuScreen::Multiplayer:
			entrybox->handleInput(window);
			entrybox->setFocus(true);
			for (int i = 3; i < 7; i++)
			{
				if (mButtons.at(i)->getGlobalBounds().contains(mouseX, mouseY))
				{
					if (!isSelected[i])
					{
						audiomanager.playSound(SoundEffect::Select);
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
					shipId = 0;
					
				}
				else
				{
					
					if (isSelected[4])
					{
						
						isJoined = true;
						shipId = 1;
						
					}
					else
					{
						if (isSelected[5])
						{
							isJoined = false;
							currentScreen = MenuScreen::Main;
						}
						else 
						{
							if (isSelected[6])
							{
								std::ofstream outfile;
								outfile.open("ip.txt");
								outfile << entrybox->getText();
								outfile.close();
								startGame = true;
							}
						}
					}
				}
				isClicked = false;
			}
			break;

		case MenuScreen::About:
			if (mButtons.at(5)->getGlobalBounds().contains(mouseX, mouseY))
			{
				if (!isSelected[5])
				{
					audiomanager.playSound(SoundEffect::Select);
					isSelected[5] = true;
					mButtons.at(5)->setColor(sf::Color::Red);
				}
			}
			else
			{
				if (isSelected[5])
				{
					isSelected[5] = false;
					mButtons.at(5)->setColor(sf::Color::White);
				}
			}

			if (isClicked)
			{
				if (isSelected[5])
					currentScreen = MenuScreen::Main;
			}
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
		mTextBox.at(0)->render(window);
		break;
	case MenuScreen::Multiplayer:
		mButtons.at(3)->render(window);
		mButtons.at(5)->render(window);
		if (isJoined)
		{
			entrybox->render(window);
			mButtons.at(6)->render(window);
		}
		else
		{
			mButtons.at(4)->render(window);
		}
		mTextBox.at(0)->render(window);
		break;
	case MenuScreen::About:
		for (int k = 0; k < 3; k++)
		{
			mTextBox.at(k)->render(window);
		}
		mButtons.at(5)->render(window);
	}

    window.display();
}

// Bug in cursor in About Page and readText is not rendered.