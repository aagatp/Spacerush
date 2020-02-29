#pragma once
#include "widget.h"

class EntryBox :public Widget
{
public:
	typedef std::shared_ptr<EntryBox> entryboxPtr;
	EntryBox();
	void handleInput(sf::RenderWindow& window);
	std::string getText();
	void render(sf::RenderTarget& target) override;
	void setAttributes(sf::Font& font);
	void setPos(const sf::Vector2f&) override;
	bool contains(sf::Vector2f);
	void setFocus(bool);
private:
	std::string m_string;
	sf::Text m_text, askEntry;
	bool isFocus;
	sf::RectangleShape rect;
};