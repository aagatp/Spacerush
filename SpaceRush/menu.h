#pragma once
#include <memory>
#include "scene.h"
#include "scenemanager.h"
#include "resourceholder.h"
#include "resourceidentifiers.h"
#include "button.h"
#include "textbox.h"

enum class MenuScreen
{
    Main,
    Multiplayer,
    About,
};

class Menu :public Scene
{
public:
    Menu(SceneManager& sceneManager, sf::RenderWindow& window);
    ~Menu();
    void processEvents();
    void update(const sf::Time& dt);
    void draw();
private:
    int shipId;
    sf::Sprite bgSprite;
    sf::Font mFont;
    std::vector<Button::buttonPtr>mButtons;
    std::vector<TextBox::textboxPtr> mTextBox;
    MenuScreen currentScreen;
    bool isSelected[6];
    bool isClicked;
    int mouseX, mouseY;
    bool startGame;
};

