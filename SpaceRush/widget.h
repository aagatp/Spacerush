#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "resourceholder.h"
#include "resourceidentifiers.h"

class Widget
{
public:
	Widget() = default;
	virtual void render(sf::RenderTarget& renderer) = 0;
	virtual void setPos(const sf::Vector2f& pos) = 0;
};
