#include "gameplay.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

GamePlay::GamePlay(SceneManager& sceneManager, sf::RenderWindow& window)
    : Scene{sceneManager, window} 
{

}

GamePlay::~GamePlay() 
{
}


void GamePlay::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            sceneManager.quit();
            return;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::Escape:
                sceneManager.quit();
                return;
            }
        }
    }
}

void GamePlay::update(const sf::Time& dt)
{

}

void GamePlay::draw() {
    window.clear(sf::Color::Red);
    window.display();
}