#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "Map.h"
#include "Gui.h"

#include "Batiment.h"
#include "Maison.h"


int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Gestion Isometrique");
    window.setFramerateLimit(60);

    Map map;
    Gui interface(window);

	Maison maison;

    sf::View view = window.getDefaultView();

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
			interface.handleEvent(*event);
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  view.move({ -5.f, 0.f });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) view.move({ 5.f, 0.f });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    view.move({ 0.f, -5.f });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  view.move({ 0.f, 5.f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))  interface.setSelectedItemIndex("");
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && interface.getSelectedItemIndex() != "")
            map.placeObject(window, interface.getSelectedItemIndex());

        window.clear();

        window.setView(view);
        map.draw(window);
		map.objectDraw(window);

        map.detectMouse(window, interface);

        if (interface.getSelectedItemIndex() != "") {
			 maison.PreviewPlacement(window, 32.f);
        }

        interface.draw(window);

        window.display();
    }
    return 0;
}