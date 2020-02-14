#pragma once

#include "widget.h"
#include <string>

class TextBox : public Widget
{
public:
    TextBox();
    typedef std::shared_ptr<TextBox> textboxPtr;
    void render(sf::RenderTarget& renderer) override;
    void setPos(const sf::Vector2f& pos)   override;
    void setAttributes(const std::string& text, int size, sf::Font& font);
    void setColor(const sf::Color color);

private:
    sf::Vector2f m_position;
    sf::Text m_textbox;
};