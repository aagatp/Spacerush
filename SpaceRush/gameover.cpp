#include "gameover.h"
#include "menu.h"
#include <iostream>

GameOver::GameOver(SceneManager& sceneManager, sf::RenderWindow& window, int winner) :
	Scene{ sceneManager,window }, mouseX(0), mouseY(0), isClicked(false),isSelected(false),quit(false)
{
	std::cout << " Drawn ";

	window.setMouseCursorVisible(true);
	float screenWidgth = window.getSize().x;
	float screenHeight = window.getSize().y;
	
	sf::Texture& bgTexture = bgTextures.get(Textures::Space);
	bgTexture.setRepeated(true);
	sf::Vector2i pos(screenWidgth / 2, screenHeight / 2);
	sf::Vector2i size(screenWidgth, screenHeight);
	bgSprite.setTextureRect(sf::IntRect(pos, size));
	bgSprite.setTexture(bgTexture);
	sf::Font& mFont = fontholder.get(Fonts::Game);

	auto winText = std::make_shared<TextBox>();
	winText->setAttributes("GAME OVER", 60, mFont);
	winText->setPos({ screenWidgth / 2 - winText->getSize() / 2, 200 });
	winText->setColor(sf::Color::Red);

	auto exitBtn = std::make_shared<Button>();
	exitBtn->setAttributes("Exit", 40, mFont);
	exitBtn->setPos({ screenWidgth - 300,screenHeight - 100 });
	exitBtn->setColor(sf::Color::White);
	mButton = exitBtn;

	if (winner == 1)
		winnerName = "You win the game.";
	else
		winnerName = "Opponent Wins the game. ";

	auto gameText = std::make_shared<TextBox>();
	gameText->setAttributes(winnerName, 40, mFont);
	gameText->setPos({ screenWidgth / 2 - gameText->getSize() / 2, 500});
	gameText->setColor(sf::Color::Magenta);
	mTextBox = gameText;
	wintext = winText;
}
GameOver::~GameOver()
{

}

void GameOver::processEvents() {
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
void GameOver::update(const sf::Time& dt)
{
	if (quit == false)
	{
		if (mButton->getGlobalBounds().contains(mouseX, mouseY))
		{
			if (!isSelected)
			{
				isSelected = true;
				mButton->setColor(sf::Color::Red);
			}
			if (isClicked && isSelected)
				quit = true;
		}
		else
		{
			if (isSelected)
			{
				isSelected = false;
				mButton->setColor(sf::Color::White);
			}
		}
	}
	else
	{
		std::unique_ptr<Scene> menu(new Menu(sceneManager, window));
		sceneManager.changeScene(std::move(menu));
	}
}

void GameOver::draw()
{
	window.clear(sf::Color::Black);
	window.draw(bgSprite);
	mButton->render(window);
	wintext->render(window);
	mTextBox->render(window);
	window.display();
}
