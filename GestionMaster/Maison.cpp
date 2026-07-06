#include "Maison.h"
Maison::Maison() {
	gain = 1;
	shape.setSize({ 32.f * 3, 32.f * 3});
	shape.setOrigin({ shape.getSize().x / 3, shape.getSize().y / 3 });
	shape.setFillColor(sf::Color::Green);
}