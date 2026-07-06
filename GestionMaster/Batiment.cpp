#include "Batiment.h"

void Batiment::PreviewPlacement(sf::RenderWindow& window, float sizeTile) {
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);

    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

    float snappedX = std::floor(mouseWorldPos.x / sizeTile) * sizeTile;
    float snappedY = std::floor(mouseWorldPos.y / sizeTile) * sizeTile;

    shape.setPosition({ snappedX, snappedY });

    shape.setFillColor(sf::Color(255, 255, 255, 128));

    window.draw(shape);
}