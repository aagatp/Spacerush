#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "scene.h"
#include "gameplay.h"

Menu::Menu(SceneManager& sceneManager, sf::RenderWindow& window)
    : Scene{ sceneManager, window } {
}


void Menu::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            sceneManager.quit();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::Space: {
                std::unique_ptr<Scene> gameState(new GamePlay(sceneManager,window));
                sceneManager.changeScene(std::move(gameState));
                return;
            }
            case sf::Keyboard::Escape:
                sceneManager.quit();
                return;
            }
        }
    }
}

void Menu::update(const sf::Time& dt) {

}

void Menu::draw() {
    window.clear(sf::Color::Black);
    window.display();
}