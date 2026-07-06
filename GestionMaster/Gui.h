#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

using json = nlohmann::json;
class Gui {
public:
	Gui(sf::RenderWindow& window);
	void button();

	void draw(sf::RenderWindow& window);
	void afficherBoutiqueTGUI();


	void setOpenShop(bool open) { openShop = open; }
	bool isShopOpen() const { return openShop; }
	int getMoney() const { return money; }
	void handleEvent(const sf::Event& event) { gui.handleEvent(event); }
	sf::String getSelectedItemIndex() const { return selectedItemIndex; }
	void setSelectedItemIndex(const sf::String& index) { selectedItemIndex = index; }


private:
	tgui::Gui gui;

	sf::Font font;
	sf::Font fontArticle;
	std::unique_ptr<sf::Text> text;
	json shopData;

	sf::String selectedItemIndex = "";

	bool openShop = false;
	int money = 100000;

};

