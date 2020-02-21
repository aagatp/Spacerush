#include "gameplay.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "gameover.h"

GamePlay::GamePlay(SceneManager& sceneManager, sf::RenderWindow& window, int shipId)
    : Scene{sceneManager, window},shipId(shipId), mWorld(window,shipId),gamePlay(0)
{
    window.setMouseCursorVisible(true);
    float screenWidgth = window.getSize().x;
    float screenHeight = window.getSize().y*30;

    sf::Texture& bgTexture = bgTextures.get(Textures::Space);
    bgTexture.setRepeated(true);
    sf::Vector2i pos(screenWidgth / 2, screenHeight / 2);
    sf::Vector2i size(screenWidgth, screenHeight);
    bgSprite.setTextureRect(sf::IntRect(pos, size));
    bgSprite.setTexture(bgTexture);
}

GamePlay::~GamePlay() 
{
}


void GamePlay::processEvents() {
    sf::Event event;

    if (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed|| event.key.code==sf::Keyboard::Escape)
        {
            sceneManager.quit();
        }
    }
}

void GamePlay::update(const sf::Time& dt)
{
    if (gamePlay == 0)
    {
        mWorld.update(dt);
        if (mWorld.checkGameStatus() == 1)
        {
            gamePlay = 1;
        }
        else if (mWorld.checkGameStatus() == 2)
        {
            gamePlay = 2;
        }
        mWorld.handleInputs();
    }
    else
    {
        std::unique_ptr<Scene> gameOver(new GameOver(sceneManager, window, gamePlay));
        sceneManager.changeScene(std::move(gameOver));
    }
}

void GamePlay::draw() {
    window.clear(sf::Color::Black);
    window.draw(bgSprite);
    mWorld.draw();
}