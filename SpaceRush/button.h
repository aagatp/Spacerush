#pragma once

#include "widget.h"
#include <string>

class Button : public Widget
{
public:
    Button();
    typedef std::shared_ptr<Button> buttonPtr;
    void render(sf::RenderTarget& renderer) override;
    void setPos(const sf::Vector2f& pos)   override;
    void setAttributes(const std::string& text, int size, sf::Font& font);
    sf::FloatRect getGlobalBounds();
    void setColor(const sf::Color color);
    int getSize();

private:
    sf::Vector2f m_position;
    sf::Text mText;
};