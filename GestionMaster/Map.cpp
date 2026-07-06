#include "Map.h"
#include <iostream>

Map::Map() {
    saveMap.resize(sizeX, std::vector<int>(sizeY));
    saveMapObject.resize(sizeX, std::vector<int>(sizeY));


    auto loadTexture = [](const std::string& path) -> sf::Texture {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            return texture;
        }
        std::cerr << "Erreur : Impossible de charger " << path << "\n";
        return sf::Texture{};
        };

    textureWater = loadTexture("assets/SpriteMap/water1.png");
    textureGrass = loadTexture("assets/SpriteMap/grass.png");
    textureGrassCoinHD = loadTexture("assets/SpriteMap/grass_coin_hd.png");
    textureGrassCoinHG = loadTexture("assets/SpriteMap/grass_coin_hg.png");
    textureGrassCoinBD = loadTexture("assets/SpriteMap/grass_coin_bd.png");
    textureGrassCoinBG = loadTexture("assets/SpriteMap/grass_coin_bg.png");
    textureGrassCoinInterHD = loadTexture("assets/SpriteMap/grass_coin_inter_hd.png");
    textureGrassCoinInterHG = loadTexture("assets/SpriteMap/grass_coin_inter_hg.png");
    textureGrassCoinInterBD = loadTexture("assets/SpriteMap/grass_coin_inter_bd.png");
    textureGrassCoinInterBG = loadTexture("assets/SpriteMap/grass_coin_inter_bg.png");
    textureGrassFlanH = loadTexture("assets/SpriteMap/grass_flan_h.png");
    textureGrassFlanG = loadTexture("assets/SpriteMap/grass_flan_g.png");
    textureGrassFlanB = loadTexture("assets/SpriteMap/grass_flan_b.png");
    textureGrassFlanD = loadTexture("assets/SpriteMap/grass_flan_d.png");

    sprite = std::make_unique<sf::Sprite>(textureWater);

    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(1);
    tile.setSize({ 32.f, 32.f });

    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            saveMap[i][j] = 0;
        }
    }

    generateIsland();
    //creationMap();

    std::cout << "Map created" << std::endl;
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            std::cout << saveMap[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Map::creationMap() {
    for (int i = 1; i < sizeX; i++) {
        for (int j = 1; j < sizeY; j++) {
            if (saveMap[i][j] != 0) {
                if (saveMap[i - 1][j] == 0) {
                    saveMap[i][j] = 1;
                }
            }
        }
    }
}

void Map::generateIsland() {
    for (int x = 1; x < sizeX - 1; x++) {
        for (int y = 1; y < sizeY - 1; y++) {
            saveMap[x][y] = 9;
        }
    }

    for (int i = 1; i < sizeX; i++) {
        for (int j = 1; j < sizeY; j++) {
            if (saveMap[i][j] != 0) {
                if (saveMap[i - 1][j] == 0) {
                    saveMap[i][j] = 1;
                }
            }
        }
    }
}

void Map::detectMouse(sf::RenderWindow& window, const Gui& gui) {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    int tileX = static_cast<int>(worldPos.x / sizeTile);
    int tileY = static_cast<int>(worldPos.y / sizeTile);

    if (tileX < 0 || tileY < 0 ||
        tileX >= static_cast<int>(saveMap.size()) ||
        tileY >= static_cast<int>(saveMap[tileX].size()))
        return;

    if (saveMap[tileX][tileY] != 0) {
        tile.setPosition({ static_cast<float>(tileX * sizeTile), static_cast<float>(tileY * sizeTile) });
        tile.setFillColor(sf::Color(255, 255, 255, 100));
        window.draw(tile);
    }
}

void Map::placeObject(sf::RenderWindow& window, const sf::String& item) {
    std::cout << "Placing object: " << item.toAnsiString() << std::endl;
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	std::cout << "Mouse world position: (" << worldPos.x << ", " << worldPos.y << ")\n";

    std::cout << tile.getSize().x << " " << tile.getSize().y << std::endl;

    int tileX = static_cast<int>(worldPos.x / sizeTile);
    int tileY = static_cast<int>(worldPos.y / sizeTile);
    if (tileX < 0 || tileY < 0 ||
        tileX >= static_cast<int>(saveMap.size()) ||
        tileY >= static_cast<int>(saveMap[tileX].size()))
        return;
    
    if (item == "Maison") {

		if (saveMap[tileX][tileY] == 0 || 
            saveMap[tileX][tileY-1] == 0 ||
            saveMap[tileX][tileY+1] == 0 ||
            saveMap[tileX-1][tileY] == 0 ||
            saveMap[tileX-1][tileY-1] == 0 ||
            saveMap[tileX-1][tileY+1] == 0 ||
            saveMap[tileX+1][tileY] == 0 ||
            saveMap[tileX+1][tileY-1] == 0 ||
            saveMap[tileX+1][tileY+1] == 0) {
            std::cout << "Cannot place object on water at: (" << tileX << ", " << tileY << ")\n";
			return;
		}

	    saveMapObject[tileX][tileY] = 1;
        saveMapObject[tileX][tileY] = 1;
        saveMapObject[tileX][tileY - 1] = 1;
        saveMapObject[tileX][tileY + 1] = 1;
        saveMapObject[tileX - 1][tileY] = 1;
        saveMapObject[tileX - 1][tileY - 1] = 1;
        saveMapObject[tileX - 1][tileY + 1] = 1;
        saveMapObject[tileX + 1][tileY] = 1;
        saveMapObject[tileX + 1][tileY - 1] = 1;
        saveMapObject[tileX + 1][tileY + 1] = 1;
	    std::cout << "Object placed at: (" << tileX << ", " << tileY << ")\n";
        maison.setSize({ static_cast<float>(sizeTile), static_cast<float>(sizeTile) });
        maison.setPosition({ static_cast<float>(tileX * sizeTile), static_cast<float>(tileY * sizeTile) });
        maison.setFillColor(sf::Color::Cyan);
    }

	//afficherMap(saveMapObject);
}

void Map::draw(sf::RenderWindow& window) {
    if (!sprite) return;

    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (saveMap[i][j] == 0)      sprite->setTexture(textureWater);
            else if (saveMap[i][j] == 1) sprite->setTexture(textureGrassFlanH);
            else if (saveMap[i][j] == 2) sprite->setTexture(textureGrassCoinInterHD);
            else if (saveMap[i][j] == 3) sprite->setTexture(textureGrassFlanD);
            else if (saveMap[i][j] == 4) sprite->setTexture(textureGrassCoinInterBD);
            else if (saveMap[i][j] == 5) sprite->setTexture(textureGrassFlanB);
            else if (saveMap[i][j] == 6) sprite->setTexture(textureGrassCoinInterBG);
            else if (saveMap[i][j] == 7) sprite->setTexture(textureGrassFlanG);
            else if (saveMap[i][j] == 8) sprite->setTexture(textureGrassCoinInterHG);
            else if (saveMap[i][j] == 9) sprite->setTexture(textureGrass);

            auto textureSize = sprite->getTexture().getSize();

            sprite->setScale({ static_cast<float>(sizeTile) / textureSize.x, static_cast<float>(sizeTile) / textureSize.y });
            sprite->setPosition({ static_cast<float>(i * sizeTile), static_cast<float>(j * sizeTile) });

            window.draw(*sprite);
        }
    }
}

void Map::objectDraw(sf::RenderWindow& window) {
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            if (saveMapObject[x][y] == 1) {
                maison.setPosition({ static_cast<float>(x * sizeTile), static_cast<float>(y * sizeTile) });
                window.draw(maison);
            }
        }
    }
}


// ======================= PRIVATE METHODS =======================

void Map::afficherMap(const std::vector<std::vector<int>>& map) {
    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}