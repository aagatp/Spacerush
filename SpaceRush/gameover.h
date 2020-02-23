#pragma once
#include <memory>
#include "scene.h"
#include "scenemanager.h"
#include "resourceholder.h"
#include "resourceidentifiers.h"
#include "button.h"
#include "textbox.h"
class GameOver :
	public Scene
{
public:
	GameOver(SceneManager& sceneManager, sf::RenderWindow& window, int winner);
	~GameOver();
	void processEvents();
	void update(const sf::Time& dt);
	void draw();
private:
	sf::Sprite bgSprite;
	sf::Font mFont;
	std::string winnerName;
	Button::buttonPtr mButton;
	TextBox::textboxPtr mTextBox;
	bool isClicked, quit;
	int mouseX, mouseY;
	bool isSelected;
};

