#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "resourceholder.h"
#include "resourceidentifiers.h"
//#include "animation.h"
class Spaceship
{
public:
    Spaceship(int);


    sf::Vector2f getPosition(); 
    void setPosition(sf::Vector2f); 

    sf::FloatRect getBounds(); //Returns the bounding box to check collision

    void decreaseHealth(int); 
    unsigned int getHealth(); 
    void setHealth(unsigned int); //Set the health bar to this value

    bool checkDestroyed(); 

    void move(sf::Vector2f); 
    float getAngle();
    void setAngle(float);
    void render(sf::RenderTarget& l_window);
    sf::IntRect getTextureRect();
    const sf::Texture* getTexture();
    const sf::Transform getInverseTransform();
private:

    sf::RectangleShape healthbar;
    TextureHolder shipTex;
    sf::Sprite spaceship;
    float m_angle;
    sf::IntRect rect;
    sf::Vector2f m_position;
    int m_playerid;
    unsigned int m_health = 100;
    bool m_destroyed = false;
    int speed;
};
