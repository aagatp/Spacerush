#include "application.hpp"
#include <SFML/Graphics.hpp>

Application::Application():window(sf::VideoMode(200, 200), "SFML works!")
{

}
void Application::run()
{
    while (window.isOpen())
    {
        processInputs();
        render();
    }

}
void Application::processInputs()
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Application::render()
{

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.clear();
    window.draw(shape);
    window.display();
}
void Application::update()
{

}