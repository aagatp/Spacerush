#include "entrybox.h"

EntryBox::EntryBox() :rect({ 300, 40}), isFocus(false)
{
    rect.setOutlineThickness(2);
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Red);
    askEntry.setString("Enter Server Ip: ");
}
void EntryBox::setAttributes(sf::Font& font)
{
    m_text.setFont(font);
    m_text.setFillColor(sf::Color::Black);
    askEntry.setFont(font);
}
void EntryBox::setPos(const sf::Vector2f& pos)
{
    m_text.setPosition({ pos.x + 2,pos.y + 2 });
    rect.setPosition(pos);
    askEntry.setPosition(pos - sf::Vector2f{400, 0});
}

std::string EntryBox::getText()
{
    return m_text.getString();
}
bool EntryBox::contains(sf::Vector2f point)
{
    return rect.getGlobalBounds().contains(point);
}
void EntryBox::setFocus(bool focus) {
    isFocus = focus;
}
void EntryBox::handleInput(sf::RenderWindow& window) {
    sf::Event e;
    if (window.pollEvent(e))
    {
        if (!isFocus || e.type != sf::Event::TextEntered)
            return;

        if (e.text.unicode == 8) {   // Delete key
            m_string = m_string.substr(0, m_string.size() - 1);
        }
        else if (m_string.size() < 20) {
            m_string += e.text.unicode;
        }
        m_text.setString(m_string);        
    }
}
void EntryBox::render(sf::RenderTarget& target)
{
    
    target.draw(rect);
    target.draw(m_text);
    target.draw(askEntry);
}