#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "resourceholder.h"
#include "resourceidentifiers.h"
class Spaceship
{
public:
    Spaceship(int);

    void destroy(); //Destroys the tank

    sf::Vector2f getPosition(); //Returns the current position of the tank
    void setPosition(sf::Vector2f); //Sets the tank to the current position

    sf::FloatRect getBounds(); //Returns the bounding box to check collision

    void decreaseHealth(int); //Decrease the health of the player by given amount
    unsigned int getHealth(); //Returns the current health
    void setHealth(unsigned int); //Set the health to this value

    bool checkDestroyed(); //check if the tank has been destroyed 

    void move(sf::Vector2f); //move the tank to specific direction
    float getAngle();
    void setAngle(float);
    void render(sf::RenderTarget& l_window);
private:

    sf::RectangleShape healthbar;
    TextureHolder shipTex;
    sf::Sprite spaceship;
    float m_angle;

    sf::Vector2f m_position;

    int m_playerid;
    unsigned int m_health = 100;
    bool m_destroyed = false;

    unsigned int bullet_no;
};
