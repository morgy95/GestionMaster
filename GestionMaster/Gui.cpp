#include "Gui.h"
#include <iostream>
#include <fstream>

Gui::Gui(sf::RenderWindow& window) : gui(window)
{
    tgui::Font textButton("assets/font/Pixelitta-Regular.ttf");
    if (!font.openFromFile("assets/font/Pixelitta-Regular.ttf")) {
        std::cerr << "Erreur Pixelitta-Regular.ttf\n";
    }

    if (!fontArticle.openFromFile("assets/font/Tsuchigumo.ttf")) {
        std::cerr << "Erreur Tsuchigumo.ttf\n";
    }

    openShop = false;

    // 3. CHARGER LE JSON
    std::ifstream f("Shop.json");
    if (f.is_open()) {
        shopData = json::parse(f);
    }

    // 4. CRÉER LE BOUTON APRES QUE LA GUI SOIT CONFIGURÉE
    auto button = tgui::Button::create("Boutique");
    if (button) {
        button->setPosition({ 50.f, 50.f });
        button->setSize({ 150.f, 40.f });
        button->getRenderer()->setFont(textButton);

        button->onClick([this]() {
			afficherBoutiqueTGUI();
        });

        button->onMouseEnter([button]() {
            button->getRenderer()->setTextColor(tgui::Color::Black);
            button->getRenderer()->setTextColor(tgui::Color::White);
            });

        button->onMouseLeave([button]() {
            button->getRenderer()->setTextColor(tgui::Color::White);
		    button->getRenderer()->setTextColor(tgui::Color::Black);
            });

        gui.add(button);
    }
}

void Gui::draw(sf::RenderWindow& window) {
    gui.draw();
}

void Gui::afficherBoutiqueTGUI() {
    auto panel = tgui::Panel::create();
    panel->setPosition({ 30.f, 100.f });
    panel->setSize({ 700.f, 400.f });

    panel->getRenderer()->setBackgroundColor(tgui::Color(50, 50, 50));

    float yOffset = 20.f;

    for (auto& item : shopData) {
        std::string name = item["name"];
        int cost = item["cost"];

        auto label = tgui::Label::create(name + " - Cout: " + std::to_string(cost));
        label->setPosition({ 20.f, yOffset });
        label->getRenderer()->setTextColor(tgui::Color::White);

        label->onClick([this, name]() {
            std::cout << "Achat de l'article " << name << std::endl;
            selectedItemIndex = name;
        });

        panel->add(label);
        yOffset += 40.f;
    }

    if (openShop) {
        openShop = false;
		gui.remove(gui.get("ShopPanel"));
		std::cout << "Boutique cachée\n";
    }
    else {
        openShop = true;
        gui.add(panel, "ShopPanel");
		std::cout << "Boutique affichée\n";
    }
}