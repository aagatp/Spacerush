#pragma once
namespace function {
	const float PI = 3.14159265;
	inline sf::Vector2f normalize(sf::Vector2f& vec) {
		vec *= 1 / sqrt(pow(vec.x, 2) + pow(vec.y, 2));
		return vec;
	}
	inline float magnitude(sf::Vector2f& vec) { return sqrt(pow(vec.x, 2) + pow(vec.y, 2)); }
	
}