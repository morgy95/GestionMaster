#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Batiment {
public:
	Batiment() = default;
	void PreviewPlacement(sf::RenderWindow& window, float sizeTile);
private:

protected:
	int vie;
	int gain;
	sf::RectangleShape shape;
};

