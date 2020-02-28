#include "spaceship.h"
#include "functions.h"
Spaceship::Spaceship(int a) :m_playerid(a), m_angle(0)
{
    healthbar.setSize({ static_cast<float>(m_health), 15 });
    
    healthbar.setOutlineColor(sf::Color::White);
    healthbar.setOutlineThickness(2);
    sf::IntRect def(sf::IntRect(153, 0, 153, 153));
    if (a == 0)
    {
        //shipTex.load(Textures::Spaceship, "Assets/sheet.png"); //sprite sheet not in position
        shipTex.load(Textures::Spaceship, "Assets/blue.png"); // But this is working ...
        spaceship.setTexture(shipTex.get(Textures::Spaceship));

        spaceship.setOrigin({
            spaceship.getGlobalBounds().width / 2 + spaceship.getOrigin().x,
            spaceship.getGlobalBounds().height / 2 + spaceship.getOrigin().y
            });
        healthbar.setFillColor(sf::Color::Cyan);
        spaceship.setPosition({100,500});
        healthbar.setPosition(50, 600);
    }
    if (a == 1)
    {
        shipTex.load(Textures::Spaceship, "Assets/redspaceship.png");
        spaceship.setTexture(shipTex.get(Textures::Spaceship));
        spaceship.setOrigin({
            spaceship.getGlobalBounds().width / 2 + spaceship.getOrigin().x,
            spaceship.getGlobalBounds().height / 2 + spaceship.getOrigin().y
            });
        healthbar.setFillColor(sf::Color::Red);
        spaceship.setPosition({ 800, 500});
        healthbar.setPosition(750, 600);
    }
    //spaceship.setTextureRect(def);
}


void Spaceship::move(sf::Vector2f pos)
{
    speed = function::magnitude(pos);
    spaceship.move(-pos);
    healthbar.move(-pos);
    //std::cout << speed << '\n';
}
void Spaceship::setAngle(float angle)
{
    m_angle = angle;
    spaceship.setRotation(angle);
    //healthbar.setRotation(angle);
}


void Spaceship::decreaseHealth(int amount)
{
    if (m_health <= 10)
    {
        m_destroyed = true;
    }
    m_health = m_health - amount;
    healthbar.setSize({ static_cast<float>(m_health), 15 });
}

sf::FloatRect Spaceship::getBounds()
{
    return spaceship.getGlobalBounds();
}
sf::IntRect Spaceship::getTextureRect()
{
    return spaceship.getTextureRect();
}
const sf::Texture* Spaceship::getTexture()
{
    return spaceship.getTexture();
}
const sf::Transform Spaceship::getInverseTransform()
{
    return spaceship.getInverseTransform();
}

unsigned int Spaceship::getHealth() { return m_health; }

bool Spaceship::checkDestroyed() { return m_destroyed; }

sf::Vector2f Spaceship::getPosition() { return spaceship.getPosition(); }

void Spaceship::setPosition(sf::Vector2f position)
{
    spaceship.setPosition(position);
    healthbar.setPosition(position +sf::Vector2f(-50, 100));
}

void Spaceship::setHealth(unsigned int l_health)
{
    m_health = l_health;
    healthbar.setSize({ static_cast<float>(m_health), 15 });
}

float Spaceship::getAngle() { return m_angle; }


void Spaceship::render(sf::RenderTarget& l_window)
{
    
    //spaceship.setTextureRect(sf::IntRect(speed*153,0,153,153)); //animation logic not working

    l_window.draw(spaceship);
    l_window.draw(healthbar);
}