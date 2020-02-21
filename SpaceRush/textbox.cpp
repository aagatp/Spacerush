#include "textbox.h"

#include <iostream>

TextBox::TextBox() :m_textbox()
{
}

void TextBox::setAttributes(const std::string& text, int size, sf::Font& font)
{
    m_textbox.setString(text);
    m_textbox.setCharacterSize(size);
    m_textbox.setFont(font);
}


void TextBox::render(sf::RenderTarget& renderer)
{
    renderer.draw(m_textbox);
}
void TextBox::setColor(sf::Color color)
{
    m_textbox.setFillColor(color);
}
void TextBox::setPos(const sf::Vector2f& pos)
{
    m_position = pos;
    m_textbox.setPosition(m_position);
}
int TextBox::getSize()
{
    return m_textbox.getGlobalBounds().width;
}
