#include "button.h"
#include <iostream>

Button::Button():mText()
{
}

void Button::setAttributes(const std::string& text, int size, sf::Font& font)
{
    mText.setString(text);
    mText.setCharacterSize(size);
    mText.setFont(font);
}

void Button::render(sf::RenderTarget& renderer)
{
    renderer.draw(mText);
}
sf::FloatRect Button::getGlobalBounds()
{
    return mText.getGlobalBounds();
}
void Button::setColor(const sf::Color color)
{
    mText.setFillColor(color);
}

void Button::setPos(const sf::Vector2f& pos)
{
    m_position = pos;
    mText.setPosition(m_position);
}
int Button::getSize()
{
    return mText.getGlobalBounds().width;
}