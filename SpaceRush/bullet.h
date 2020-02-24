#pragma once
#include <SFML/Graphics.hpp>
#include "resourceholder.h"
#include "resourceidentifiers.h"
class Bullet
{
public:
    Bullet(int, sf::Vector2f, sf::Vector2f direction);
    ~Bullet();
    
    sf::Vector2f getPosition();
    sf::Vector2f getDirection();
    void setPosition(sf::Vector2f);
    void render(sf::RenderTarget& l_window);

    sf::FloatRect getBounds();

    void move(sf::Vector2f); //Move the bullet in the direction
    bool isOutOfBounds();
    int yAxisLife;
	static void loadTextures();
    sf::IntRect getTextureRect();
    const sf::Texture* getTexture();
    const sf::Transform getInverseTransform();

private:

    sf::Sprite bullet;
    static TextureHolder bulletTex;

    int shipId;
    sf::Vector2f ship_position;
    sf::Vector2f m_position;
    sf::Vector2f acceleration;
    sf::Vector2f m_direction;
};

