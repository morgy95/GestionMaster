#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "Gui.h"
#pragma once

class Map
{
public:
    Map();
    void creationMap();
    void generateIsland();
    void detectMouse(sf::RenderWindow& window, const Gui& gui);
    void placeObject(sf::RenderWindow& window, const sf::String& item);
	void draw(sf::RenderWindow& window);
    void objectDraw(sf::RenderWindow& window);


private:

    void afficherMap(const std::vector<std::vector<int>>& map);

    static const int sizeTile = 32;
    int sizeX = 30;
    int sizeY = 20;

    std::vector<std::vector<int>> saveMap;
    std::vector<std::vector<int>> saveMapObject;
  
    sf::RectangleShape maison;
    sf::RectangleShape tile;

	sf::Texture textureWater;

    sf::Texture textureGrass;
    sf::Texture textureGrassCoinHD;
    sf::Texture textureGrassCoinHG;
    sf::Texture textureGrassCoinBD;
    sf::Texture textureGrassCoinBG;

    sf::Texture textureGrassCoinInterHD;
    sf::Texture textureGrassCoinInterHG;
    sf::Texture textureGrassCoinInterBD;
    sf::Texture textureGrassCoinInterBG;

    sf::Texture textureGrassFlanH;
    sf::Texture textureGrassFlanG;
    sf::Texture textureGrassFlanB;
    sf::Texture textureGrassFlanD;

    sf::Texture textureHover;


    std::unique_ptr<sf::Sprite> sprite;
};