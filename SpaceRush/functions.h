#pragma once
namespace function {
	const float PI = 3.14159265;
	sf::Vector2f normalize(sf::Vector2f& vec) {
		vec *= 1 / sqrt(pow(vec.x, 2) + pow(vec.y, 2));
		return vec;
	}
	float magnitude(sf::Vector2f& vec) { return sqrt(pow(vec.x, 2) + pow(vec.y, 2)); }
}