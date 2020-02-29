#include "gameplay.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "gameover.h"
#include <thread>
GamePlay::GamePlay(SceneManager& sceneManager, sf::RenderWindow& window, int shipId)
    : Scene{sceneManager, window},shipId(shipId), mWorld(window,shipId),gamePlay(0)
{
    window.setMouseCursorVisible(true);
    float screenWidgth = window.getSize().x;
    float screenHeight = window.getSize().y * 30;
    sf::Texture& bgTexture = bgTextures.get(Textures::Space);
    bgTexture.setRepeated(true);
    sf::Vector2i pos(screenWidgth / 2, screenHeight / 2);
    sf::Vector2i size(screenWidgth, screenHeight);
    bgSprite.setTextureRect(sf::IntRect(pos, size));
    bgSprite.setTexture(bgTexture);
    if (shipId == 0)
    {
        otherId = 1;
        server = new Server();
        client = new Client(sf::IpAddress::getLocalAddress());
        server->recieveConnection();
        server->recieveConnection();
        server->thread();
    }
    else
    {
        otherId = 0;
        client = new Client();
        client->sendConnection();
        
    }
    client->thread();

}

GamePlay::~GamePlay() 
{
    delete server;
    delete client;
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
    if (gamePlay == 1 || gamePlay == 2)
    {
        std::unique_ptr<Scene> gameOver(new GameOver(sceneManager, window, gamePlay));
        sceneManager.changeScene(std::move(gameOver));
    }
    if (gamePlay == 0 && window.hasFocus())
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
        sf::Packet pack{ mWorld.getStatus() };
        client->send(pack);
        mWorld.setOtherPlayers(otherId, client->getPosition(otherId), client->getHealth(otherId), client->getDirection(otherId), client->isShooting(otherId));
    }
}

void GamePlay::draw() {
    window.clear(sf::Color::Black);
    window.draw(bgSprite);
    mWorld.draw();
    window.display();
}